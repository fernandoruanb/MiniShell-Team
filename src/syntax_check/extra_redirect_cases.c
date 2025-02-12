/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_redirect_cases.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:42:58 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/12 16:56:00 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	extra_redirect_cases(t_token *root, t_utils *data)
{
	if ((root->id == REDIRECT_IN || root->id == REDIRECT_OUT
			|| root->id == APPEND)
		&& root->next != NULL && root->next->id == FD)
		return (1);
	return (show_error_fd("Syntax: REDIRECT Error", 0, data, 0));
}
