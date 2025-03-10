/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:43:23 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/10 11:00:48 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **str)
{
	int	i;

	printf("echo built in \n");
	if (!str)
		return (!printf("\n"));
	i = 0;
	while (str[i])
		printf("%s", str[i++]);
	printf("\n");
	return (0);
}
