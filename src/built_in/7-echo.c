/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:43:23 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/10 11:15:07 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **str)
{
	int	i;
	int	nl;

	if (!str)
		return (!printf("\n"));
	nl = ft_strcmp(str[0], "-n") != 0;
	i = !nl;
	while (str[i])
		printf("%s ", str[i++]);
	if (nl)
		printf("\n");
	return (0);
}
