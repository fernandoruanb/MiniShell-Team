/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:52 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/07 12:49:44 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*try_redir(t_ast **root, t_data *data, int *fd)
{
	int	*origin;

	if (!*root)
		return (fd);
	//origin = manage_redir(root, data);
	fd = try_redir(&(*root)->left, data, fd);
	fd = try_redir(&(*root)->right, data, fd);
	restore_redirect(fd);
	origin = manage_redir(root, data);
	return (origin);
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
	if (ast->id == PIPE)
		exec_multi_cmd(&ast, data);
	exec_single_cmd(&ast, data);
	data->prompt->exit_status = data->utils.exec_status;
	return (0);
}
