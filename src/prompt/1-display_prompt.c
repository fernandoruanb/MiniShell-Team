/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-display_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:25:21 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/07 11:37:33 by jopereir         ###   ########.fr       */
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

// static void	ft_free(void *a, void *b)
// {
// 	free(a);
// 	free(b);
// }

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

void	display_prompt(t_data *data)
{
	char	*name;

	name = ft_strdup("\033[1;36m<<Master of universe(mini)>>$ \033[0m");
	// while (1)
	// {
	// 	data->prompt->input = readline(name);
	// 	if (!prompt->input)
	// 		return (ft_exit(name, data, 0));
	// 	if (ft_strncmp(prompt->input, "exit", 4) == 0)
	// 		return (ft_exit(name, data, 0));
	// 	add_history(prompt->input);
	// 	exec_cmd(prompt);
	// 	ft_free(prompt->input, name);
	// }
	char	*temp = ft_strdup("<infile cat> outfile -e");
	data->token = lexer(temp, data->prompt->envp);
	token_print(data->token);
	token_clean(data->token);
	free(temp);
	free(name);
}
