/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-display_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:25:21 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/24 13:40:19 by jopereir         ###   ########.fr       */
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
	temp = ft_strchr(ft_strnstr(src, "home", len),'/');
	temp++;
	dst = ft_calloc(len + 3, 1);
	if (!dst)
		return (NULL);
	ft_strcpy(dst, src);
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

void	display_prompt(t_prompt *prompt)
{
	char	*path;

	while (1)
	{
		path = get_name();
		printf("\033[1;33m%s\033[0m ", path);
		prompt->input = readline(NULL);
		if (!prompt->input)
		{
			rl_clear_history();
			printf("\n");
			return (ft_free(path, prompt->input));
		}
		add_history(prompt->input);
		exec_cmd(prompt);
		ft_free(prompt->input, path);
	}
}
