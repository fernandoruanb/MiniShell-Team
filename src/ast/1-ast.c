/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:04:26 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/28 17:14:55 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cmd(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	while(str[i] && str[i] != ' ')
		i++;
	temp = ft_calloc(i + 1, 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		temp[i] = str[i];
		i++;
	}
	return (str[i]);	
}

static char	**get_args(char *str)
{
	int		i;
	char	**temp;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	temp = ft_split(&str[i], ' ');
	if (!temp)
		return (NULL);
	return (temp);
}

t_ast	*ast_create(char *input, t_ast *parent)
{
	t_ast	*new;

	new = ft_calloc(1, sizeof(t_ast));
	if (!new)
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	new->parent = parent;
	new->cmd = get_cmd(input);
	new->argv = get_args(input);	
	return (new);
}

t_ast	*ast_add(t_ast *root, char *input)
{
	if (!root)
		return (create_ast(input, root));
	
	/*
		Criar as condições para decidir o lado da lista
	*/
	root->left = add_node(root->left, input);
	root->right = add_node(root->right, input);
	return (root);
}

void	ast_destroy(t_ast *root)
{
	if (!root)
		return ;
	ast_destroy(root->left);
	ast_destroy(root->right);
	free(root);
}
