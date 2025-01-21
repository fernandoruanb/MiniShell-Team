/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:40:06 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/21 10:54:37 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_tree
{
	int				value;

	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

t_tree	*new_tree(int value)
{
	t_tree	*new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->value = value;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_tree	*add_tree(t_tree *root, int value)
{
	if (!root)
		return (new_tree(value));
	if (value < root->value)
		root->left = add_tree(root->left, value);
	else
		root->right = add_tree(root->right, value);
	return (root);
}

void	print_tree(t_tree *root)
{
	if (!root)
		return ;
	print_tree(root->left);
	printf("%d ", root->value);
	print_tree(root->right);
}

void	destroy_tree(t_tree *root)
{
	if (!root)
		return ;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

int	main(void)
{
	t_tree	*node;

	node = new_tree(15);
	node = add_tree(node, 25);
	node = add_tree(node, 4);
	node = add_tree(node, 2);
	node = add_tree(node, 10);
	node = add_tree(node, 100);
	node = add_tree(node, 99);
	print_tree(node);
	printf("\n");
	destroy_tree(node);
}
