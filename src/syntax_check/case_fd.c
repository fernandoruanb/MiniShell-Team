/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:34:42 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/12 16:49:05 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	case_fd(t_token *root, t_utils *data)
{
	if (is_number(root, data))
		return (check_is_valid_fd(root, data));
	if (check_is_directory(root, data))
		return (show_error_fd("Syntax: FD Error", 0, data, 0));
	if ((data->status == 0) && (!is_number(root, data)))
		return (show_error_fd("Syntax: FD Error", 0, data, 0));
	data->status = 2;
	if (is_number(root, data) && root->next != NULL
		&& root->next->id == REDIRECT_IN)
		return (1);
	if (root->id == FD && root->next != NULL && root->next->id == REDIRECT_OUT)
		return (1);
	if (root->id == FD && root->previous == NULL)
		return (show_error_fd("Syntax: FD Error", 0, data, 0));
	else if ((root->id == FD) && (root->previous != NULL)
		&& (root->previous->id == REDIRECT_OUT
			|| root->previous->id == APPEND
			|| root->previous->id == REDIRECT_IN))
		return (1);
	else if (root->previous != NULL && root->previous->id == ARG)
		return (1);
	return (show_error_fd("Syntax: FD Error", 0, data, 0));
}
