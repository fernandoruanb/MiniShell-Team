/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:40:06 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/21 12:07:31 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

typedef struct s_tree
{
	pid_t			pid;

	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

void	hello(void);
void	destroy_tree(t_tree *root);

t_tree	*new_tree(int value)
{
	t_tree	*new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->pid = value;
	new->left = NULL;
	new->right = NULL;
	if (new->pid == -1)
		exit(1);
	if (new->pid == 0)
		hello();
	waitpid(new->pid, NULL, 0);
	return (new);
}

t_tree	*add_tree(t_tree *root, int value)
{
	if (!root)
		return (new_tree(value));
	if (value < root->pid)
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
	printf("%d ", root->pid);
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

void	hello(void)
{
	printf("Hello from %d\n", getpid());
}

int	main(void)
{
	t_tree	*node;
	t_tree	*temp;

	node = new_tree(fork());
	if (node->pid != 0)
	{
		node = add_tree(node, fork());
		node = add_tree(node, fork());
		node = add_tree(node, fork());
		destroy_tree(node);
	}
}
