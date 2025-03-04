/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-make_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:34:17 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/28 11:10:38 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_ast	*make_ast(t_token **token)
// {
// 	t_token *temp;
// 	t_ast	*new;

// 	temp = *token;
// 	new = NULL;
// 	while (temp->next)
// 		temp = temp->next;
// 	while (temp->previous)
// 	{
// 		if (temp->id != CMD && temp->id != ARG)
// 			new = add_node(new, &temp);
// 		temp = temp->previous;
// 	}
// 	while (temp)
// 	{
// 		if (temp->id == CMD || temp->id == FD || temp->id == LIMITER)
// 			new = add_node(new, &temp);
// 		temp = temp->next;
// 	}
// 	return (new);
// }

static void	handle_operators(t_token **token, t_ast **ast)
{
	t_token	*temp;

	if (!*token)
		return ;
	temp = *token;
	handle_operators(&temp->next, ast);
	if (temp->id == OPERATOR_AND || temp->id == OPERATOR_OR)
		*ast = add_node(*ast, &temp);
}

static int	isredir(t_id id)
{
	return (id == REDIRECT_IN || id == REDIRECT_OUT || id == APPEND || id == HEREDOC);
}

static void	handle_pipe_redir(t_token **token, t_ast **ast)
{
	t_token	*temp;

	if (!*token)
		return ;
	temp = *token;
	handle_pipe_redir(&temp->next, ast);
	if (temp->id == PIPE || isredir(temp->id))
		*ast = add_node(*ast, &temp);
}

static void handle_commands(t_token **token, t_ast **ast)
{
	t_token	*temp;

	if (!*token)
		return ;
	temp = *token;
	handle_commands(&temp->next, ast);
	if (temp->id == CMD || temp->id == FD || temp->id == LIMITER)
		*ast = add_node(*ast, &temp);
}

void	make_ast(t_token **token, t_ast **ast)
{
	if (!*token)
		return ;
	handle_operators(token, ast);
	handle_pipe_redir(token, ast);
	handle_commands(token, ast);
}
