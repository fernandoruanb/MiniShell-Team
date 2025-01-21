/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:56:07 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/21 10:01:13 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

typedef struct s_binary_tree
{
	int	value;
	struct s_binary_tree	*left_branch;
	struct s_binary_tree	*right_branch;
}	t_binary_tree;

t_binary_tree	*ft_lstnew(int value)
{
	t_binary_tree	*new;

	new = malloc(sizeof(t_binary_tree));
	if (!new)
		return (NULL);
	new->value = value;
	new->left_branch = NULL;
	new->right_branch = NULL;
	return (new);
}

t_binary_tree	*add_value(t_binary_tree *root, int value)
{
	if (!root)
		return (ft_lstnew(value));
	if (value < root->value)
		root->left_branch = add_value(root->left_branch, value);
	else
		root->right_branch = add_value(root->right_branch, value);
	return (root);
}

void	print_tree(t_binary_tree *root)
{
	if (!root)
		return ;
	print_tree(root->left_branch);
	printf("%d ", root->value);
	print_tree(root->right_branch);
}

void	free_binary_tree(t_binary_tree *root)
{
	if (!root)
		return ;
	free_binary_tree(root->left_branch);
	free_binary_tree(root->right_branch);
	free(root);
}

int	main(void)
{
	t_binary_tree	*root;

	root = NULL;
	root = ft_lstnew(2);
	root = add_value(root, 3);
	root = add_value(root, 1);
	root = add_value(root, 10);
	print_tree(root);
	printf("\n");
	free_binary_tree(root);
	return (0);
}
