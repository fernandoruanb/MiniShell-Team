/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.1-manage_redir_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:11:48 by jonas             #+#    #+#             */
/*   Updated: 2025/03/12 15:28:11 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*save_origin(t_data *data)
{
	int	*new;

	new = ft_calloc(2, sizeof(int));
	if (!new)
		return (NULL);
	new[0] = dup(0);
	new[1] = dup(1);
	data->flags.shoud_restore = !data->flags.shoud_restore;
	return (new);
}

void	destroy_fd(int **fd)
{
	if (!fd || !*fd)
		return ;
	close ((*fd)[0]);
	close ((*fd)[1]);
	free(*fd);
	*fd = NULL;
}

void	make_redir(int fd, int fd2)
{
	if (fd < 0 || fd2 < 0)
		return ;
	if (dup2(fd, fd2) < 0)
		close (fd);
}
