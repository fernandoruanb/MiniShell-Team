/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:34:42 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/17 09:34:56 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_pipes_cases_fd(t_token *root)
{
	t_token	*last;

	last = root;
	while (last->previous)
	{
		if (last->id == PIPE)
			return (1);
		last = last->previous;
	}
	last = root;
	while (last->next)
	{
		if (last->id == PIPE)
			return (1);
		last = last->next;
	}
	return (0);
}

static int	invalid_fd(t_token *root)
{
	t_token	*last;

	if (check_pipes_cases_fd(root))
		return (0);
	last = root;
	if (last->previous)
		last = last->previous;
	while (last->previous)
	{
		if (last->id == FD)
		{
			if (ft_strcmp(last->str, root->str) == 0)
				return (0);
		}
		last = last->previous;
	}
	if (root->previous != NULL && root->previous->id == REDIRECT_IN)
		if (access(root->str, F_OK) != 0)
			return (1);
	return (0);
}

int	case_fd(t_token *root, t_utils *data)
{
	if (invalid_fd(root))
		return (show_error_fd("Syntax: FD Error", 0, data, 0));
	if (is_number(root))
		return (check_is_valid_fd(root, data));
	if (check_is_directory(root, data))
		return (show_error_fd("Syntax: FD Error", 0, data, 0));
	if ((data->status == 0) && (!is_number(root)))
		return (show_error_fd("Syntax: FD Error", 0, data, 0));
	data->status = 2;
	if (is_number(root) && root->next != NULL
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
