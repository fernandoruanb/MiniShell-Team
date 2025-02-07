/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid_things.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:49:14 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 13:49:30 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_invalid_things(t_token *root)
{
	if ((root->id == OPERATOR_AND || root->id == OPERATOR_OR)
		&& (root->next != NULL) && (root->previous != NULL)
		&& (root->next->id == PIPE || root->previous->id == PIPE
			|| root->next->id == OPERATOR_AND
			|| root->previous->id == OPERATOR_AND
			|| root->next->id == OPERATOR_OR
			|| root->previous->id == OPERATOR_OR))
		return (1);
	return (0);
}
