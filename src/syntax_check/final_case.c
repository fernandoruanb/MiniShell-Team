/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:16:30 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 12:16:46 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (root->next == NULL && data->redirects != data->files)
		return (1);
	if (root->next == NULL && data->commands == 0 && data->args > 0)
		return (show_error_fd("You put args but never a command", 1, data, 0));
	if (root->next == NULL && data->commands < data->pipes)
		return (show_error_fd("You have so many pipes.", 1, data, 0));
	if (check_invalid_brackets_position(data))
		return (show_error_fd("You inverted brackets", 1, data, 0));
	return (0);
}
