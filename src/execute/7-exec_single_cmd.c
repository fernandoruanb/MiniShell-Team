/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7-exec_single_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:16:20 by jonas             #+#    #+#             */
/*   Updated: 2025/03/09 13:45:39 by jonas            ###   ########.fr       */
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
	ast = *root;
	cmd = find_cmd(&ast);
	if (!handle_builtin(ast->cmd, data))
		single_command(&cmd, data);
	//data->prompt->exit_status = data->utils.exec_status;
}
