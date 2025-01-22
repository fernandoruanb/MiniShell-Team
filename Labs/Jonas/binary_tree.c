/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:40:06 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/21 14:01:58 by jopereir         ###   ########.fr       */
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

t_tree	*new_tree(pid_t pid)
{
	t_tree	*new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->pid = pid;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_tree	*add_tree(t_tree *root, pid_t pid)
{
	if (!root)
		return (new_tree(pid));
	if (pid < 0)
		root->left = add_tree(root->left, pid);
	else
		root->right = add_tree(root->right, pid);
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

void	run_nodes(t_tree *root)
{
	if (!root)
		return ;
	if (root->pid == 0)
	{
		printf("Hello from %d\n", getpid());
		exit (0);
	}
	else
	{
		run_nodes(root->right);
		wait(NULL);
	}
}

int	main(void)
{
	t_tree	*root;
	t_tree	*node;
	pid_t	pid;
	int		i;

	root = new_tree(getpid());
	i = 0;
	while (i < 4)
	{
		pid = fork();
		root = add_tree(root, pid);
		i++;
	}
	run_nodes(root);
	destroy_tree(root);
}
