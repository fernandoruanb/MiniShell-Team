/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-remove_escape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:26:40 by jonas             #+#    #+#             */
/*   Updated: 2025/02/19 13:41:08 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_escape(char *str)
{
	int		i;
	int		j;
	char	*new;

	if (!str)
		return (NULL);
	new = ft_calloc(ft_strlen(str) + 1, 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			i++;
			continue ;
		}
		new[j++] = str[i++];
	}
	free(str);
	return (new);
}
