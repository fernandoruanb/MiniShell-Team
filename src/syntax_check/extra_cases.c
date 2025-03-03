/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:31:16 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/12 16:54:04 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	extra_cases(t_token *root, t_utils *data)
{
	if (root->id == BRACKET_O || root->id == BRACKET_C)
		return (check_brackets(root, data));
	if (root->next == NULL && data->brackets_o != data->brackets_c)
		return (show_error_fd("Syntax: OPERATOR Error", 0, data, 0));
	if (root->id == OPERATOR_AND && data->status == 0)
		return (show_error_fd("Syntax: OPERATOR Error", 0, data, 0));
	if (root->id == OPERATOR_OR && data->status == 0)
		return (show_error_fd("Syntax: OPERATOR Error", 0, data, 0));
	data->status = 2;
	if (check_invalid_things(root))
		return (show_error_fd("Syntax: Invalid input", 0, data, 0));
	if ((root->id == OPERATOR_AND) && (root->previous == NULL
			|| root->next == NULL))
		return (show_error_fd("Syntax: OPERATOR Error", 0, data, 0));
	if ((root->id == OPERATOR_OR) && (root->previous == NULL
			|| root->next == NULL))
		return (show_error_fd("Syntax: OPERATOR Error", 0, data, 0));
	return (1);
}
