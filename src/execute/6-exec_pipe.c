/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6-exec_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:48:09 by jonas             #+#    #+#             */
/*   Updated: 2025/03/17 15:16:24 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	getlastcmd(int index, t_token **token)
{
	t_token	*tkn;
	int		i;

	if (!*token)
		return (0);
	tkn = *token;
	i = 0;
	while (tkn)
	{
		if (tkn->id == CMD && tkn->index > i)
			i = tkn->index;
		tkn = tkn->next;
	}
	return (index == i);
}

static int	getfirstcmd(int index, t_token **token)
{
	t_token	*tkn;

	if (!*token)
		return (0);
	tkn = *token;
	while (tkn)
	{
		if (tkn->id == CMD)
			return (index == tkn->index);
		tkn = tkn->next;
	}
	return (0);
}

static void	call_handle_pipe(t_ast *ast, t_data *data)
{
	if (ast->id != CMD)
		return ;
	if (getfirstcmd(ast->index, &data->token))
		handle_pipe_op(&ast, 1, data);
	else if (getlastcmd(ast->index, &data->token))
		handle_pipe_op(&ast, 2, data);
	else
		handle_pipe_op(&ast, 3, data);
}

int	exec_pipe(t_ast **root, t_data *data)
{
	t_ast	*ast;

	if (!*root)
		return (1);
	ast = *root;
	call_handle_pipe(ast, data);
	return (0);
}
