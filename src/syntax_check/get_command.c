/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:12:00 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/15 20:55:40 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_command(t_token *root, t_utils *data)
{
	if (final_case(root, data))
		return (show_error_fd("Syntax: Invalid input", 0, data, 0));
	if (root->id == PIPE)
		return (case_pipe(root, data));
	else if (root->id == LIMITER)
		return (case_limiter(root, data));
	else if (root->id == OPERATOR_AND
		|| root->id == OPERATOR_OR || root->id == BRACKET_O
		|| root->id == BRACKET_C)
		return (extra_cases(root, data));
	else if (root->id == REDIRECT_IN || root->id == REDIRECT_OUT
		|| root->id == APPEND || root->id == HEREDOC)
		return (case_redirect(root, data));
	else if (root->id == FD)
		return (case_fd(root, data));
	else if (root->id == CMD)
		return (case_command(root, data));
	else if (root->id != CMD && data->status == 0)
		return (show_error_fd("Syntax: Invalid input", 0, data, 0));
	if (root->next == NULL && data->brackets_o != data->brackets_c)
		return (show_error_fd("Syntax: Invalid input", 0, data, 0));
	if (root->id == ARG)
		return (case_arg(root, data));
	return (show_error_fd("Syntax: Invalid input", 0, data, 0));
}
