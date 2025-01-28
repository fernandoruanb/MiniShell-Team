/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-display_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:25:21 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/27 15:59:43 by jopereir         ###   ########.fr       */
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

static char	*get_name(int flag)
{
	char	*dir_path;
	char	*prompt;
	int		len;

	if (flag)
		return (ft_strdup("<<Master of universe(mini)>>"));
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

static char	*colours(char *str, char *c1, char *c2)
{
	char	*temp;
	char	*temp2;
	char	*yellow_text;

	temp = ft_calloc(ft_strlen(c1) + 1, 1);
	if (!temp)
		return (NULL);
	ft_strcpy(temp, c1);
	temp2 = ft_strjoin(temp, str);
	free(temp);
	yellow_text = ft_strjoin(temp2, c2);
	free(temp2);
	return (yellow_text);
}

void	display_prompt(t_prompt *prompt)
{
	char	*path;
	char	*c_path;

	while (1)
	{
		path = get_name(1);
		
		//Yellow
		//c_path = colours(path, "\033[1;33m", "\033[0m");

		//Cyan
		c_path = colours(path, "\033[1;36m", "\033[0m");
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
