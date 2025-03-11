/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:43:23 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/11 10:29:48 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_str(char **str, int i)
{
	while (str[i])
	{
		printf("%s", str[i++]);
		if (str[i])
			printf(" ");
	}
}

int	ft_echo(char **str)
{
	int	i;
	int	nl;

	if (!str)
		return (!printf("\n"));
	nl = ft_strcmp(str[0], "-n") != 0;
	i = !nl;
	put_str(str, i);
	if (nl)
		printf("\n");
	return (0);
}
