/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:25:21 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/21 17:21:11 by jopereir         ###   ########.fr       */
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

void	ft_free(void *a, void *b)
{
	free(a);
	free(b);
}

void	display_prompt(void)
{
	char	*path;
	char	*input;

	while (1)
	{
		path = get_name();
		input = readline(path);
		if (!input)
		{
			rl_clear_history();
			printf("\n");
			return (ft_free(path, input));
		}
		add_history(input);
		printf("You have typed: %s\n", input);
		ft_free(input, path);
	}
}
