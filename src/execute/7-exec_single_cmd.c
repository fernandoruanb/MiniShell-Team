/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-exec_single_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:16:20 by jonas             #+#    #+#             */
/*   Updated: 2025/03/14 12:56:28 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exec_single_cmd(t_ast **root, t_data *data)
{
	t_ast	*ast;
	t_ast	*cmd;

	if (!*root || (*root)->id == PIPE)
		return ;
	data->fd = save_origin(data);
	if (manage_redir(&data->token, data))
	{
		restore_redirect(data->fd, data);
		return ;
	}
	ast = *root;
	cmd = find_cmd(&ast);
	if (cmd && !handle_builtin(cmd->cmd, data))
		single_command(&cmd, data);
	restore_redirect(data->fd, data);
}
