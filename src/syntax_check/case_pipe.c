/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:46:55 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 12:47:08 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	case_pipe(t_token *root, t_utils *data)
{
	if (data->status == 0)
		return (show_error_fd("Pipe is the first to appear.", 0, data, 0));
	data->status = 2;
	if (root->next != NULL && root->next->id == BRACKET_O)
		return (1);
	if (root->next != NULL && (root->next->id == REDIRECT_OUT
			|| root->next->id == REDIRECT_IN || root->next->id == APPEND
			|| root->next->id == HEREDOC))
		return (1);
	if ((root->id == PIPE) && (root->previous == NULL
			|| root->next == NULL))
		return (show_error_fd("PIPE next or previous", 0, data, 0));
	else if (data->status != 0 && root->next->id != CMD)
		return (show_error_fd("PIPE next elements isn't a CMD", 0, data, 0));
	return (1);
}
