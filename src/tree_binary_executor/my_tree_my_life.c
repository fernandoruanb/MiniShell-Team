/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_tree_my_life.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:06:43 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/18 19:53:53 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef struct s_tree
{
	char	*value;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

void	free_split(char **value)
{
	int	i;

	if (!value)
		return ;
	i = 0;
	while (value[i] != NULL)
		free(value[i++]);
	value = NULL;
}

t_tree	*create_new_branch(char *value)
{
	t_tree	*branch;

	if (!value)
		return (NULL);
	branch = malloc(sizeof(t_tree));
	if (!branch)
		return (NULL);
	branch->value = value;
	branch->left = NULL;
	branch->right = NULL;
	return (branch);
}

void	clean_tree(t_tree **tree)
{
	if (*tree == NULL)
		return ;
	clean_tree(&(*tree)->left);
	clean_tree(&(*tree)->right);
	(*tree)->value = NULL;
	(*tree)->left = NULL;
	(*tree)->right = NULL;
	free(*tree);
	*tree = NULL;
}

void	show_tree(t_tree *tree, int level)
{
	int	index;

	if (tree == NULL)
		return ;
	show_tree(tree->right, level + 1);
	index = 0;
	while (index++ < level)
		printf("\t");
	printf("%s\t\n", tree->value);
	show_tree(tree->left, level + 1);
}

void	luke_i_m_your_father(t_token *root)
{
	while (root->next)
	{
		if (root->id == OPERATOR_AND || root->id == OPERATOR_AND)
			root->index = 1;
		else if (root->id == PIPE)
			root->index = 2;
		else if (root->id == REDIRECT_OUT || root->id == APPEND
			|| root->id == REDIRECT_IN || root->id == HEREDOC)
			root->index = 3;
		else if (root->id == CMD || root->id == FD || root->id == LIMITER)
			root->index = 4;
		else if (root->id == BRACKET_O)
			root->index = 5;
		else if (root->id == BRACKET_C)
			root->index = 6;
		else if (root->id == ARG)
			root->index = -1;
		root = root->next;
	}
}

int	my_tree_my_life(t_token *root, t_utils *data)
{
	(void)data;
	while (root->previous)
		root = root->previous;
	luke_i_m_your_father(root);
	ft_printf("My tree my life is working...\n");
	return (1);
}
