/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:28:39 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/18 15:20:05 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../../include/minishell.h"

typedef struct s_tree
{
	char	*value;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

size_t	get_len(char **commands);

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
	int	i;

	if (tree == NULL)
		return ;
	show_tree(tree->right, level + 1);
	i = 0;
	while (i++ < level)
		printf("\t");
	printf("%s\t\n", tree->value);
	show_tree(tree->left, level + 1);
}

int	detect_id(char *value)
{
	if (ft_strcmp(value, "&&") == 0 || ft_strcmp(value, "||") == 0)
		return (1);
	else if (ft_strcmp(value, "|") == 0)
		return (2);
	else if (ft_strcmp(value, ">") == 0 || ft_strcmp(value, ">>") == 0
		|| ft_strcmp(value, "<") == 0
		|| ft_strcmp(value, "<<") == 0)
		return (3);
	else
		return (4);
}

void	add_branchs_first(t_tree **tree, char *value)
{
	t_tree	*last;

	if (!(*tree))
	{
		*tree = create_new_branch(value);
		return ;
	}
	last = *tree;
	while (last->left)
		last = last->left;
	last->left = create_new_branch(value);
}

void	left_case(char **commands, t_tree **tree, char *value)
{
	int	index;

	if (!value)
		return ;
	index = 0;
	while (commands[index] != NULL)
	{
		if (ft_strcmp(commands[index], value) == 0)
			add_branchs_first(tree, commands[index]);
                index++;
	}
}

size_t	get_len(char **commands)
{
	size_t	length;

	length = 0;

	while (commands[length] != NULL)
		length++;
	return (length);
}

int	main(void)
{
	t_tree	*tree;
	char	*commands[] = {"ls -l", ">", "out", ">", "out2", ">", "invalid"};
	int	index;

	tree = NULL;
	left_case(commands, &tree, "&&");
	left_case(commands, &tree, "|");
	left_case(commands, &tree, ">");
	left_case(commands, &tree, ">>");
	left_case(commands, &tree, "<");
	left_case(commands, &tree, "<<");
	if (ft_strcmp(commands[0], "&&") != 0 && ft_strcmp(commands[0], "||") != 0
		&& ft_strcmp(commands[0], "|") != 0 && ft_strcmp(commands[0], ">") != 0
		&& ft_strcmp(commands[0], ">>") != 0 && ft_strcmp(commands[0], "<") != 0)
		add_branchs_first(&tree, commands[0]);
	if (tree)
	{
		show_tree(tree, 1);
		clean_tree(&tree);
	}
	return (0);
}
