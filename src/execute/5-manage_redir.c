/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-manage_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:38:03 by jonas             #+#    #+#             */
/*   Updated: 2025/03/07 13:20:23 by jopereir         ###   ########.fr       */
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
	if (id == REDIRECT_IN || id == HEREDOC)
		fd = handle_red_in(name, data);
	else if (id == REDIRECT_OUT)
		fd = handle_redirect_out(name, data);
	else if (id == APPEND)
		fd = append(name, data);
	return (fd);
}

static void	aplly_redirect(int fd, t_id id)
{
	if (fd < 0)
		return ;
	make_redir(fd, id == APPEND || id == REDIRECT_OUT);
	close (fd);
}

void	manage_redir(t_ast **root, t_data *data)
{
	int	fd;

	printf("Manage_redir foi chamado: %d\n", (*root)->index);
	if (!*root || !isredir((*root)->id))
		return ;
	printf("Manage_redir vai executar: %d\n", (*root)->index);
	fd = switch_redir(root, (*root)->id, &data->utils);
	aplly_redirect(fd, (*root)->id);
}

void	restore_redirect(int *original)
{
	if (!original || (original[0] < 0 || original[1] < 0))
		return ;
	if (dup2 (original[1], 1) < 0)
		perror("Restore STDOUT error: ");
	if (dup2 (original[0], 0) < 0)
		perror("Restore STDIN error: ");
	destroy_fd(original);
}
