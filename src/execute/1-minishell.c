/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:52 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/19 11:26:06 by jonas            ###   ########.fr       */
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


// static void	exec_multi_cmd(t_ast **root, t_data *data)
// {
// 	t_ast	*ast;
// 	int		*fd;

// 	if (!*root || !data)
// 		return ;
// 	ast = *root;
// 	fd = NULL;
// 	if (isredir(ast->id))
// 	{
// 		fd = save_origin(data);
// 		if (manage_redir(&data->token, data))
// 		{
// 			restore_redirect(fd, data);
// 			return ;
// 		}
// 	}
// 	if (ast->id != CMD)
// 	{
// 		exec_multi_cmd(&ast->left, data);
// 		exec_multi_cmd(&ast->right, data);
// 	}
// 	exec_pipe(&ast, data);
// 	restore_redirect(fd, data);
// }

static int	exec_multi_cmd(t_ast **root, t_data *data)
{
	t_ast	*ast;
	int		*fd;

	if (!*root || !data)
		return (1);
	ast = *root;
	// printf("eu tenho: %s(%d)\n", ast->cmd[0], ast->index);
	fd = save_origin(data);
	if (manage_redir(&ast, &data->token, data))
	{
		restore_redirect(fd, data);
		return (1);
	}
	if (ast->id != CMD)
	{
		exec_multi_cmd(&ast->left, data);
		exec_multi_cmd(&ast->right, data);
	}
	exec_pipe(&ast, data);
	restore_redirect(fd, data);
	return (0);
}

// int	new_redir(t_token **token, t_ast **root, t_data *data)
// {
// 	t_token	*temp;
// 	t_ast	*ast;
// 	int		fd;

// 	if (!*token || !*root)
// 		return (1);
// 	temp = *token;
// 	ast = *root;
// 	while ((temp && temp->next) && temp->id != ast->id)
// 		temp = temp->next;
// 	fd = -1;
// 	while (temp && temp->id != PIPE)
// 	{
// 		if (fd)
// 			close (fd);
// 		fd = switch_redir(&temp, data);
// 		if (fd == INT_MIN || data->utils.exec_status == 130)
// 			return (1);
// 		aplly_redirect(fd, temp->id);
// 		temp = temp->next;
// 	}
// 	return (0);
// }

// static int	exec_multi_cmd(t_ast **root, t_data *data)
// {
// 	t_ast	*ast;
// 	int		*fd;
// 	int		ret;

// 	if (!*root || !data)
// 		return (0);
// 	fd = NULL;
// 	ret = 0;
// 	ast = *root;
// 	if (ast->id == PIPE)
// 	{
// 		ret = exec_multi_cmd(&ast->left, data);
// 		if (!ret)
// 			ret = exec_multi_cmd(&ast->right, data);
// 	}
// 	if (isredir(ast->id))
// 	{
// 		fd = save_origin(data);
// 		manage_redir(&data->token, data);
// 	}
// 	if (!ret)
// 		ret = exec_pipe(&ast, data);
// 	restore_redirect(fd, data);
// 	return (ret);
// }

// int	outra_função(t_ast **root, t_data *data)
// {
// 	t_ast	*ast;

// 	if (!*root || !isredir((*root)->id))
// 		return (0);
	
// 	ast = *root;
// 	while (ast && ast->left)
// 		ast = ast->left;
	
// 	return (new_redir(&data->token, ast->index, (*root)->index, data));
	
// }	

// static void	exec_multi_cmd(t_ast **root, t_data *data)
// {
// 	t_ast	*ast;

// 	if (!*root || !data)
// 		return ;
// 	ast = *root;
// 	if (ast->id == PIPE)
// 	{
// 		exec_multi_cmd(&ast->left, data);
// 		outra_função(&ast->right, data);
// 		ast = ast->right;
// 	}
	
// 	if (isredir(ast->id))
// 		while (ast && ast->left)
// 			ast = ast->left;
	
// 	exec_pipe(&ast, data);
// }

int	minishell(t_ast **root, t_data *data)
{
	t_ast	*ast;

	if (!data)
		return (1);
	printf("cheguei no minishell\n");
	ast = *root;
	if (ast->id == PIPE)
		exec_multi_cmd(&ast, data);
	exec_single_cmd(&ast, data);
	start_echo();
	return (0);
}
