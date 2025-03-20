/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.1-manage_redir_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:11:48 by jonas             #+#    #+#             */
/*   Updated: 2025/03/20 16:32:48 by jonas            ###   ########.fr       */
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
	dup2(fd, fd2);
	close (fd);
}

char	*find_fd(t_token **token)
{
	t_token	*temp;

	if (!*token)
		return (NULL);
	temp = *token;
	while (temp)
	{
		if (temp->id == FD || temp->id == LIMITER)
			return (temp->str);
		temp = temp->next;
	}
	return (NULL);
}

int	switch_redir(t_token **token, t_data *data)
{
	int		fd;
	char	*name;

	if (!*token || !data)
		return (-1);
	name = find_fd(token);
	fd = -1;
	fd = redir_out(name, (*token)->id, data);
	if (fd < 0 && fd != INT_MIN)
		fd = redir_in(name, (*token)->id, token, data);
	return (fd);
}
