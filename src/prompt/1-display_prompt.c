/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-display_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:25:21 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/07 15:31:36 by jopereir         ###   ########.fr       */
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

static int	handle_space(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\0')
			return (0);
	return (1);
}

void	display_prompt(t_data *data)
{
	while (1)
	{
		data->prompt->input = readline(BLUE"Master of universe(mini)$ "RESET);
		if (!data->prompt->input)
			ft_exit(data, NULL);
		if (handle_space(data->prompt->input))
		{
			free(data->prompt->input);
			continue ;
		}
		if (data->prompt->input[0] != '\0')
		{
			add_history(data->prompt->input);
			analysis(data);
		}
		free(data->prompt->input);
		data->prompt->input = NULL;
	}
}
