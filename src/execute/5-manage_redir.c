/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-manage_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:38:03 by jonas             #+#    #+#             */
/*   Updated: 2025/03/10 10:38:04 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_fd(t_token **token)
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

static void	aplly_redirect(int fd, t_id id)
{
	if (fd < 0)
		return ;
	make_redir(fd, id == REDIRECT_OUT || id == APPEND);
	close (fd);
}

static int	switch_redir(t_token **token, t_utils *data)
{
	int		fd;
	char	*name;

	if (!*token)
		return (-1);
	name = find_fd(token);
	fd = -1;
	if ((*token)->id == REDIRECT_OUT)
		fd = handle_redirect_out(name, data);
	else if ((*token)->id == APPEND)
		fd = append(name, data);
	else if ((*token)->id == REDIRECT_IN)
		fd = handle_red_in(name, data);
	else if ((*token)->id == HEREDOC)
		heredoc(name, data);
	return (fd);
}

int	manage_redir(t_token **token, t_data *data)
{
	int		fd;
	t_token	*temp;

	if (!*token || !data)
		return (1);
	temp = *token;
	fd = -1;
	while (temp)
	{
		if (isredir(temp->id))
		{
			fd = switch_redir(&temp, &data->utils);
			if (fd == INT_MIN)
				return (1);
			aplly_redirect(fd, temp->id);
		}
		temp = temp->next;
	}
	return (0);
}

void	restore_redirect(int *original)
{
	if (!original || (original[0] < 0 || original[1] < 0))
		return ;
	make_redir(original[0], 0);
	make_redir(original[1], 1);
	destroy_fd(original);
}
