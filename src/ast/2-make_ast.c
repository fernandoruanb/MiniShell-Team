/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-make_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:34:17 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/07 12:48:07 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	handle_pipe_ast(t_token **token, t_ast **ast)
{
	t_token	*temp;

	if (!*token)
		return ;
	temp = *token;
	handle_pipe_ast(&temp->next, ast);
	if (temp->id == PIPE)
		*ast = add_node(*ast, &temp);
}

static void	handle_commands(t_token **token, t_ast **ast, t_data *data)
{
	t_token	*temp;

	if (!*token)
		return ;
	temp = *token;
	handle_commands(&temp->next, ast, data);
	parser(&temp, data);
	if (temp->id == CMD || temp->id == FD || temp->id == LIMITER)
		*ast = add_node(*ast, &temp);
}

void	make_ast(t_token **token, t_ast **ast, t_data *data)
{
	if (!*token)
		return ;
	handle_operators(token, ast);
	handle_pipe_ast(token, ast);
	handle_redir(token, ast);
	handle_commands(token, ast, data);
}
