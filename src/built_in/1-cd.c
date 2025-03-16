/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:24:06 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/16 10:46:31 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*transform_string(char *input, int *flag)
{
	char	*home;
	char	*transformation;

	home = getenv("HOME");
	transformation = ft_strjoin(home, input + 1);
	if (!transformation)
		return (NULL);
	*flag = 1;
	return (transformation);
}

void	ft_cd(char *input)
{
	t_data	*official;
	int	flag;

	official = get_minishell();
	flag = 0;
	if (input == NULL)
		official->utils.line = getenv("HOME");
	else if (ft_strnstr(input, "~", 1))
		official->utils.line = transform_string(input, &flag);
	else if (input && flag != 1)
		official->utils.line = input;
	if (chdir(official->utils.line) == -1)
		official->utils.exec_status = 1;
	else
		official->utils.exec_status = 0;
	if (flag == 1)
		free(official->utils.line);
}
