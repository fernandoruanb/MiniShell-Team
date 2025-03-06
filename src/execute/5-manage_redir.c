/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-manage_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:38:03 by jonas             #+#    #+#             */
/*   Updated: 2025/03/06 14:55:57 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_fd(t_ast **root)
{
	char	*temp;
	if (!*root)
		return (NULL);
	if ((*root)->id == FD || (*root)->id == LIMITER)
		return ((*root)->cmd[0]);
	temp = find_fd(&(*root)->left);
	if (!temp)
		temp = find_fd(&(*root)->right);
	return (temp);
}

static int	switch_redir(t_ast **root, t_id id, t_utils *data)
{
	int		fd;
	char	*name;

	fd = -1;
	name = find_fd(root);
	if (id == REDIRECT_OUT)
		fd = handle_redirect_out(name, data);
	else if (id == APPEND)
		fd = append(name, data);
	else if (id == REDIRECT_IN)
		fd = handle_red_in(name, data);
	else if (id == HEREDOC)
		fd = heredoc(name, data);
	return (fd);
}

static void	aplly_redirect(int fd, t_id id)
{
	if (fd < 0)
		return ;
	if (id == APPEND || id == REDIRECT_OUT)
		if (dup2(fd , 1) < 0)
			perror("Redirect error: ");
	if (id == HEREDOC || id == REDIRECT_IN)
		if (dup2(fd, 0) < 0)
			perror("Redirect error: ");
	close (fd);
}

int	*manage_redir(t_ast **root, t_data *data)
{
	int	*original;
	int	fd;

	if (!*root || !isredir((*root)->id))
		return (NULL);
	original = ft_calloc(2, sizeof(int));
	if (!original)
		return (NULL);
	original[0] = dup(0);
	original[1] = dup(1);
	fd = switch_redir(root, (*root)->id, &data->utils);
	aplly_redirect(fd, (*root)->id);
	return (original);
}

void	restore_redirect(int *original)
{
	if (!original)
		return ;
	if (dup2 (original[1], 1) < 0)
		perror("Restore STDOUT error: ");
	if (dup2 (original[0], 0) < 0)
		perror("Restore STDIN error: ");
	close (original[0]);
	close (original[1]);
	free(original);
}
