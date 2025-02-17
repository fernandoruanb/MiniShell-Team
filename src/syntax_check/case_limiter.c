/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_limiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:47:56 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/17 16:50:30 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	case_limiter(t_token *root, t_utils *data)
{
	if (data->status == 0)
		return (show_error_fd("Syntax: LIMITER Error", 0, data, 2));
	data->status = 2;
	if (root->id == LIMITER && root->previous != NULL
		&& root->previous->id == HEREDOC
		&& root->next != NULL && root->next->id != LIMITER)
		return (1);
	if (root->id == LIMITER && root->previous != NULL
		&& root->previous->id == HEREDOC
		&& root->next == NULL)
		return (1);
	return (show_error_fd("Syntax: LIMITER Error", 0, data, 2));
}
