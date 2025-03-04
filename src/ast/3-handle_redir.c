/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-handle_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:14:23 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/04 10:19:29 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isredir(t_id id)
{
	return (id == REDIRECT_IN || id == REDIRECT_OUT || id == APPEND || id == HEREDOC);
}

void	handle_redir(t_token **token, t_ast **ast)
{
	t_token	*temp;

	if (!*token)
		return ;
	temp = *token;
	handle_redir(&temp->next, ast);
	if (isredir(temp->id))
		*ast = add_node(*ast, &temp);
}
