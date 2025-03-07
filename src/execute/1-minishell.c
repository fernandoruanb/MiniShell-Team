/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:26:52 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/07 12:26:56 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
