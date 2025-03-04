/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 08:25:03 by jonas             #+#    #+#             */
/*   Updated: 2025/03/04 12:57:09 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_node(char **cmd, int index, t_id id)
{
	t_ast	*new;

	new = ft_calloc(sizeof(t_ast), 1);
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->index = index;
	new->id = id;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

// static int	is_op(t_id id)
// {
// 	return (id == PIPE || id == OPERATOR_AND || id == OPERATOR_OR);
// }

t_ast	*add_node(t_ast *root, t_token **token)
{
	t_token	*temp;

	if (!root)
		return (create_node(convert_to_cmd(token), (*token)->index, (*token)->id));
	temp = *token;
	if (temp->index > root->index)
		root->right = add_node(root->right, token);
	else
		root->left = add_node(root->left, token);
	return (root); 
}

static void	print_cmd(char **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i])
			printf("%s ", cmd[i]);
		i++;
	}
}

void	print_node(t_ast *root)
{
	if (!root)
		return ;
	print_node(root->left);
	print_cmd(root->cmd);
	print_node(root->right);
}

void	clean_node(t_ast **root)
{
	if (!*root)
		return ;
	clean_node(&(*root)->left);
	clean_node(&(*root)->right);
	clear_split((*root)->cmd);
	free(*root);
	*root = NULL;
}
