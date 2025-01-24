/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:15:20 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/24 13:47:17 by jopereir         ###   ########.fr       */
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
