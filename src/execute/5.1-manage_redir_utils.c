/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.1-manage_redir_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:11:48 by jonas             #+#    #+#             */
/*   Updated: 2025/03/11 11:44:32 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*save_origin(void)
{
	int	*new;

	new = ft_calloc(2, sizeof(int));
	if (!new)
		return (NULL);
	new[0] = dup(0);
	new[1] = dup(1);
	return (new);
}

void	destroy_fd(int *fd)
{
	if (!fd)
		return ;
	close (fd[0]);
	close (fd[1]);
	free(fd);
	fd = NULL;
}

void	make_redir(int fd, int fd2)
{
	if (fd < 0 || fd2 < 0)
		return ;
	if (dup2(fd, fd2) < 0)
		perror("Redirect error: ");
}
