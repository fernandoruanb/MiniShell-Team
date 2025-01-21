/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:06:45 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/21 10:37:24 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_binary_tree
{
	int						value;
	struct s_binary_tree	*left_branch;
	struct s_binary_tree	*right_branch;
}	t_binary_tree;

t_binary_tree	*new_branch(int content)
{
	t_binary_tree	*new_branch;

	new_branch = malloc(sizeof(t_binary_tree));
	if (!new_branch)
		return (NULL);
	new_branch->value = content;
	new_branch->left_branch = NULL;
	new_branch->right_branch = NULL;
	return (new_branch);
}

t_binary_tree	*add_new_branch(t_binary_tree *root, int value)
{
	if (!root)
		return (new_branch(value));
	if (value < root->value)
		root->left_branch = add_new_branch(root->left_branch, value);
	else
		root->right_branch = add_new_branch(root->right_branch, value);
	return (root);
}

void	print_each_branch(t_binary_tree *root)
{
	if (!root)
		return ;
	print_each_branch(root->left_branch);
	printf("%d ", root->value);
	print_each_branch(root->right_branch);
}

void	free_each_branch(t_binary_tree *root)
{
	if (!root)
		return ;
	free_each_branch(root->left_branch);
	free_each_branch(root->right_branch);
	free(root);
}

int	main(void)
{
	t_binary_tree	*root;

	root = NULL;
	root = new_branch(2);
	root = add_new_branch(root, 3);
	root = add_new_branch(root, 1);
	root = add_new_branch(root, 4);
	print_each_branch(root);
	printf("\n");
	free_each_branch(root);
	return (0);
}
