/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:16:30 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/17 16:55:16 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	extra_case_cmds(t_token *root, t_utils *data)
{
	if (root->next == NULL && data->commands == 0 && data->args > 0)
		return (0);
	if (root->next == NULL && data->commands < data->pipes)
		return (show_error_fd("Syntax Error: PIPE", 1, data, 2));
	if (check_invalid_brackets_position(data))
		return (0);
	if (root->id == CMD && ft_strcmp(root->str, "./") == 0)
		return (show_error_fd("Syntax Error: CMD", 1, data, 126));
	if (root->id == CMD && !check_quotes(root))
		return (show_error_fd("Syntax Error: QUOTES", 1, data, 2));
	return (0);
}

int	final_case(t_token *root, t_utils *data)
{
	if (root->id == REDIRECT_IN || root->id == APPEND
		|| root->id == REDIRECT_OUT)
		data->redirects++;
	if (root->id == FD)
		data->files++;
	if (root->id == CMD)
		data->commands++;
	if (root->id == ARG)
		data->args++;
	if (root->id == PIPE)
		data->pipes++;
	if (root->id == BRACKET_C)
		data->index_bra_c = root->index;
	if (root->id == BRACKET_O)
		data->index_bra_o = root->index;
	return (extra_case_cmds(root, data));
}
