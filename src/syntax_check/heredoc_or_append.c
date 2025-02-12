/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_or_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:45:31 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/12 16:55:02 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_or_append(t_token *root, t_utils *data)
{
	if (root->id == HEREDOC && root->next != NULL && root->next->id == LIMITER)
	{
		data->status = 2;
		return (1);
	}
	if (root->id == HEREDOC && root->previous != NULL
		&& root->previous->id == CMD
		&& root->next != NULL && root->next->id == LIMITER)
		return (1);
	if (root->id == HEREDOC && root->previous != NULL
		&& root->previous->id == ARG
		&& root->next != NULL && root->next->id == LIMITER)
		return (1);
	if (root->id == APPEND && root->next != NULL && (root->next->id == FD))
	{
		data->status = 2;
		return (1);
	}
	if (root->id == HEREDOC && root->next != NULL
		&& root->next->id == LIMITER && root->previous != NULL
		&& root->previous->id == CMD)
		return (1);
	return (show_error_fd("Syntax: HEREDOC/APPEND Error", 0, data, 0));
}
