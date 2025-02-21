/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:24:06 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/21 11:30:14 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_cd(char *input)
// {
// 	char	*path;

// 	path = NULL;
// 	if (input[3] == '~')
// 		path = getenv("HOME");
// 	else if (input[3] == '-')
// 		path = getenv("OLDPWD");
// 	if (path == NULL)
// 	{
// 		if (chdir(input + 3) == -1)
// 			ft_printf("No such file or directory %s\n", input + 3);
// 	}
// 	else
// 		chdir(path);
// }

void	ft_cd(char *input)
{
	char	*path;

	path = NULL;
	// if (input[3] == '~')
	// 	path = getenv("HOME");
	if (!ft_strcmp(input, "-"))
		path = getenv("OLDPWD");
	if (path == NULL)
	{
		if (chdir(input) == -1)
			ft_printf("No such file or directory %s\n", input + 3);
	}
	else
		chdir(path);
}
