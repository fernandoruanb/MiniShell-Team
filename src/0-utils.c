/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:15:20 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/16 16:11:58 by jonas            ###   ########.fr       */
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

int	my_free_my_life(void *s1, void *s2, void *s3, int __return__)
{
	free(s1);
	free(s2);
	free(s3);
	return (__return__);
}
