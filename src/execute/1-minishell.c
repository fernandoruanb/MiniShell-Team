/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:52 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/12 15:04:22 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	try_redir(t_ast **root, t_data *data)
// {
// 	if (!*root)
// 		return ;
// 	printf("estou no galho: %d\n", (*root)->index);
// 	try_redir(&(*root)->left, data);
// 	try_redir(&(*root)->right, data);
// 	manage_redir(root, data);
// }

static void	exec_multi_cmd(t_ast **root, t_data *data)
{
	t_ast	*ast;
	int		*fd;

	if (!*root || !data)
		return ;
	ast = *root;
	fd = NULL;
	if (isredir(ast->id))
	{
		fd = save_origin(data);
		if (manage_redir(&data->token, data))
		{
			restore_redirect(fd, data);
			return ;
		}
	}
	if (ast->id != CMD)
	{
		exec_multi_cmd(&ast->left, data);
		exec_multi_cmd(&ast->right, data);
	}
	exec_pipe(&ast, data);
	restore_redirect(fd, data);
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
	return (0);
}
