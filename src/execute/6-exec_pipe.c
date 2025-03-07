/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6-exec_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:48:09 by jonas             #+#    #+#             */
/*   Updated: 2025/03/07 13:56:32 by jopereir         ###   ########.fr       */
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
		handle_pipe_op(&ast, 1, &data->utils);
	else if (getlastcmd(ast->index, &data->token))
		handle_pipe_op(&ast, 2, &data->utils);
	else
		handle_pipe_op(&ast, 3, &data->utils);
}

static int	isbuiltin(char **cmd)
{
	return (!ft_strcmp(cmd[0], "cd") || !ft_strncmp(cmd[0], "unset", 5)
		|| !ft_strcmp(cmd[0], "export"));
}

void	exec_pipe(t_ast **root, t_data *data)
{
	t_ast	*ast;

	if (!*root || isbuiltin((*root)->cmd))
		return ;
	ast = *root;
	call_handle_pipe(ast, data);
}
