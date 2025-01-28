/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:15:20 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/28 11:51:14 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*clear_split(char **str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*dup;

	if (!str)
		return (NULL);
	dup = ft_calloc(n + 1, 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}
