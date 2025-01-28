/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-display_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:25:21 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/28 12:55:43 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Set the dir_path to the correct format

	name/something$ command
*/
// static char	*set_dir(char *src)
// {
// 	int		len;
// 	char	*dst;
// 	int		i;
// 	char	*temp;

// 	len = ft_strlen(src);
// 	temp = ft_strchr(ft_strnstr(src, "home", len), '/');
// 	temp++;
// 	dst = ft_calloc(len + 3, 1);
// 	if (!dst)
// 		return (NULL);
// 	ft_strcpy(dst, temp);
// 	i = 0;
// 	while (dst[i])
// 		i++;
// 	dst[i++] = '$';
// 	dst[i] = ' ';
// 	return (dst);
// }

static void	ft_free(void *a, void *b)
{
	free(a);
	free(b);
}

// static char	*colours(char *str, char *c1, char *c2)
// {
// 	char	*temp;
// 	char	*temp2;
// 	char	*yellow_text;

// 	temp = ft_calloc(ft_strlen(c1) + 1, 1);
// 	if (!temp)
// 		return (NULL);
// 	ft_strcpy(temp, c1);
// 	temp2 = ft_strjoin(temp, str);
// 	free(temp);
// 	yellow_text = ft_strjoin(temp2, c2);
// 	free(temp2);
// 	return (yellow_text);
// }

static void	clear_process(char *path)
{
	rl_clear_history();
	//free(c_path);
	ft_free(path, NULL);
}

void	display_prompt(t_prompt *prompt)
{
	char	*path;
	// char	*c_path;

	while (1)
	{
		path = ft_strdup("\033[1;36m<<Master of universe(mini)>>$ \033[0m");
		
		//Yellow
		//c_path = colours(path, "\033[1;33m", "\033[0m");

		//Cyan
		//c_path = colours(path, "\033[1;36m", "\033[0m");
		prompt->input = readline(path);
		if (!prompt->input)
		{
			printf("exit\n");
			return (clear_process(path));
		}
		if (ft_strncmp(prompt->input, "exit", 4) == 0)
			return (clear_process(path));
		add_history(prompt->input);
		exec_cmd(prompt);
		//free(c_path);
		ft_free(prompt->input, path);
	}
}
