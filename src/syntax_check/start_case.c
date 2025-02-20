/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:24:39 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/20 09:09:49 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	start_case(t_token *root, t_utils *data)
{
	t_token	*last;

	last = root;
	while (last->previous)
	{
		if (last->id == PIPE)
			return (0);
		last = last->previous;
	}
	last = root;
	while (last->next)
	{
		if (last->id == PIPE || last->id == OPERATOR_AND
			|| last->id == OPERATOR_OR)
		{
			data->status = 1;
			return (1);
		}
		last = last->next;
	}
	return (0);
}
