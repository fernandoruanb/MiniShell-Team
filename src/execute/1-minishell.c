/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:52 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/06 15:45:30 by jonas            ###   ########.fr       */
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

static t_ast	*find_cmd(t_ast **root)
{
	t_ast	*ast;

	if (!*root)
		return (NULL);
	if ((*root)->id == CMD)
		return (*root);
	ast = find_cmd(&(*root)->right);
	if (!ast)
		ast = find_cmd(&(*root)->left);
	return (ast);
}

static int	*exec_cmd(t_ast	**root, t_data *data)
{
	t_ast	*ast;
	int		*fd;

	if (!*root || !data)
		return (NULL);
	ast = *root;
	fd = manage_redir(&ast, data);
	if (ast->id != CMD)
	{
		exec_cmd(&ast->left, data);
		exec_cmd(&ast->right, data);
	}
	if (ast->id == CMD)
	{
		if (getfirstcmd(ast->index, &data->token))
			handle_pipe_op(&ast, 1, &data->utils);
		else if (getlastcmd(ast->index, &data->token))
			handle_pipe_op(&ast, 2, &data->utils);
		else
			handle_pipe_op(&ast, 3, &data->utils);
	}
	restore_redirect(fd);
	return (fd);
}

int	minishell(t_ast **root, t_data *data)
{
	t_ast	*ast;
	int		*fd;

	if (!data)
		return (1);
	ast = *root;
	fd = manage_redir(&ast, data);
	if (ast->id == PIPE)
	{
		fd = exec_cmd(&ast, data);
		restore_redirect(fd);
	}
	else
		single_command(find_cmd(&ast)->cmd, &data->utils, fd);
	data->prompt->exit_status = data->utils.exec_status;
	return (0);
}
