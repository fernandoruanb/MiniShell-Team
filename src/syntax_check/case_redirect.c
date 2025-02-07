/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:41:09 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 12:41:46 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	case_redirect(t_token *root, t_utils *data)
{
	if (root->id == HEREDOC || root->id == APPEND)
		return (heredoc_or_append(root, data));
	if (data->status == 0 && (root->id == REDIRECT_IN
			|| root->id == REDIRECT_OUT || root->id == APPEND)
		&& root->next != NULL && root->next->id == FD)
	{
		data->status = 2;
		return (1);
	}
	data->status = 2;
	if (root->id == REDIRECT_IN && root->previous != NULL
		&& root->previous->id == CMD && root->next != NULL
		&& root->next->id == FD)
		return (1);
	if (root->id == REDIRECT_IN && root->next != NULL
		&& root->next->id == FD)
		return (1);
	if (root->id == REDIRECT_OUT && root->next == NULL)
		return (show_error_fd("Forgot a file after red_out", 0, data, 0));
	if (root->id == REDIRECT_OUT && root->next != NULL
		&& root->next->id != FD)
		return (show_error_fd("Forgot a file after red_out", 0, data, 0));
	if (root->id == REDIRECT_OUT && root->next->id == FD)
		return (1);
	return (extra_redirect_cases(root, data));
}
