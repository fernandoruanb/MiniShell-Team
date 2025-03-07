/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:52 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/07 13:21:15 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	try_redir(t_ast **root, t_data *data)
{
	// int	*origin;

	if (!*root || ((*root)->id == CMD || (*root)->id == FD || (*root)->id == LIMITER))
		return ;
	printf("estou no galho: %d\n", (*root)->index);
	try_redir(&(*root)->left, data);
	manage_redir(root, data);
	if (isredir((*root)->right->id))
		try_redir(&(*root)->right, data);
}

static void	exec_multi_cmd(t_ast **root, t_data *data)
{
	t_ast	*ast;

	if (!*root || !data)
		return ;
	ast = *root;
	if (ast->id == PIPE)
	{
		exec_multi_cmd(&ast->left, data);
		exec_multi_cmd(&ast->right, data);
	}
	exec_pipe(&ast, data);
}

int	minishell(t_ast **root, t_data *data)
{
	t_ast	*ast;

	if (!data)
		return (1);
	ast = *root;
	data->fd = save_origin();
	try_redir(root, data);
	if (ast->id == PIPE)
		exec_multi_cmd(&ast, data);
	exec_single_cmd(&ast, data);
	restore_redirect(data->fd);
	data->prompt->exit_status = data->utils.exec_status;
	return (0);
}
