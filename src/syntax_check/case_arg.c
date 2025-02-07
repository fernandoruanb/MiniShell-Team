/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:18:58 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 12:19:15 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	case_arg(t_token *root, t_utils *data)
{
	if (root->id == ARG && data->status == 1)
		return (1);
	else if (root->id == ARG && root->previous != NULL
		&& (root->previous->id == FD || root->previous->id == REDIRECT_OUT
			|| root->previous->id == REDIRECT_IN
			|| root->previous->id == APPEND || root->previous->id == ARG))
		return (1);
	else if (root->id == ARG && root->next != NULL && (root->next->id == ARG
			|| root->next->id == FD))
		return (1);
	else if (root->id == ARG && root->previous != NULL
		&& root->previous->id == LIMITER)
		return (1);
	return (show_error_fd("Invalid case of args", 0, data, 0));
}

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
