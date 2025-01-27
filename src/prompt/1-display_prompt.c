/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-display_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:25:21 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/27 13:34:28 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Set the dir_path to the correct format

	name/something$ command
*/
static char	*set_dir(char *src)
{
	int		len;
	char	*dst;
	int		i;
	char	*temp;

	len = ft_strlen(src);
	temp = ft_strchr(ft_strnstr(src, "home", len), '/');
	temp++;
	dst = ft_calloc(len + 3, 1);
	if (!dst)
		return (NULL);
	ft_strcpy(dst, temp);
	i = 0;
	while (dst[i])
		i++;
	dst[i++] = '$';
	dst[i] = ' ';
	return (dst);
}

static char	*get_name(void)
{
	char	*dir_path;
	char	*prompt;
	int		len;

	len = 1024;
	dir_path = ft_calloc(len, 1);
	if (!dir_path)
		return (NULL);
	if (getcwd(dir_path, len))
	{
		prompt = set_dir(dir_path);
		free(dir_path);
		return (prompt);
	}
	return (NULL);
}

static void	ft_free(void *a, void *b)
{
	free(a);
	free(b);
}

static char	*colours(char *str)
{
	char	*temp;
	char	*temp2;
	char	*yellow_text;

	temp = ft_calloc(ft_strlen("\033[1;33m") + 1, 1);
	if (!temp)
		return (NULL);
	ft_strcpy(temp, "\033[1;33m");
	temp2 = ft_strjoin(temp, str);
	free(temp);
	yellow_text = ft_strjoin(temp2, "\033[0m");
	free(temp2);
	return (yellow_text);
}

void	display_prompt(t_prompt *prompt)
{
	char	*path;
	char	*c_path;

	while (1)
	{
		path = get_name();
		c_path = colours(path);
		prompt->input = readline(c_path);
		if (!prompt->input)
		{
			rl_clear_history();
			printf("\n");
			free(c_path);
			return (ft_free(path, prompt->input));
		}
		add_history(prompt->input);
		exec_cmd(prompt);
		free(c_path);
		ft_free(prompt->input, path);
	}
}
