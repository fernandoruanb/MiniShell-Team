/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid_brackets_position.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:46:16 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 13:46:53 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_invalid_brackets_position(t_utils *data)
{
	if (data->index_bra_o != -1 && data->index_bra_c != -1)
	{
		if (data->index_bra_o > data->index_bra_c)
			return (1);
		else
		{
			data->index_bra_o = -1;
			data->index_bra_c = -1;
		}
	}
	return (0);
}
