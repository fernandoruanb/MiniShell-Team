/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:32:18 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 12:32:35 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_brackets(t_token *root, t_utils *data)
{
	if (root->id == BRACKET_C)
		data->brackets_c++;
	else if (root->id == BRACKET_O)
		data->brackets_o++;
	data->status = 2;
	if (root->id == BRACKET_O && root->next != NULL
		&& root->next->id == BRACKET_C)
		return (show_error_fd("Void brackets", 0, data, 0));
	if (root->id == BRACKET_O && root->next != NULL && root->next->id == ARG)
		return (show_error_fd("Where is the CMD in brackets?", 0, data, 0));
	if (root->id == BRACKET_C && root->next == NULL
		&& data->brackets_o != data->brackets_c)
		return (show_error_fd("Isolated BRACKET_C", 0, data, 0));
	return (1);
}
