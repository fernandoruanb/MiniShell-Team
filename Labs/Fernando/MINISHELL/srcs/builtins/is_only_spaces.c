/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_only_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:02:21 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/30 11:33:02 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

int	is_only_spaces(t_data *data)
{
	int	index;

	if (data->line[2] == '\0')
		return (1);
	index = 2;
	while (data->line[index] != '\0')
	{
		if (data->line[index] != ' ')
			return (0);
		index++;
	}
	return (1);
}
