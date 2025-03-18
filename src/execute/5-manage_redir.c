/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-manage_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:38:03 by jonas             #+#    #+#             */
/*   Updated: 2025/03/17 21:42:42 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	aplly_redirect(int fd, t_id id)
{
	int	std;

	if (fd < 0)
		return ;
	std = (id == REDIRECT_OUT || id == APPEND);
	make_redir(fd, std);
	close (fd);
}

int	switch_redir(t_token **token, t_data *data)
{
	int		fd;
	char	*name;

	if (!*token || !data)
		return (-1);
	name = find_fd(token);
	fd = -1;
	if ((*token)->id == REDIRECT_OUT)
	{
		data->utils.can_dup = false;
		fd = handle_redirect_out(name, &data->utils);
	}
	else if ((*token)->id == APPEND)
	{
		data->utils.can_dup = false;
		fd = append(name, &data->utils);
	}
	else if ((*token)->id == REDIRECT_IN)
	{
		data->utils.exec_status = true;
		fd = handle_red_in(name, &data->utils);
	}
	else if ((*token)->id == HEREDOC)
	{
		data->utils.can_dup = true;
		fd = heredoc(name, data, token);
	}
	return (fd);
}

static t_token	*get_pos(t_token **token, t_ast *root)
{
	t_token	*temp;

	if (!*token | !root)
		return (NULL);
	temp = *token;
	while ((temp && temp->next)
					&& (temp->id == PIPE || temp->index != root->index))
		temp = temp->next;
	return (temp);
}

// static int	num_sei(t_token **token)
// {
// 	t_token	*temp;

// 	if (!*token)
// 		return (1);
// 	temp = *token;
// 	while (temp)
// 	{
// 		if (isredir(temp->id))
// 			return (0);
// 		temp = temp->next;
// 	}
// 	return (1);
// }

int	manage_redir(t_ast **root, t_token **token, t_data *data)
{
	int		fd;
	t_token	*temp;

	if (!*token || !data || !*root || !isredir((*root)->id))
		return (0);
	printf("recebi: %s(%d)\n", (*root)->cmd[0], (*root)->index);
	temp = get_pos(token, find_cmd(root));
	fd = -1;
	while (temp && temp->id != PIPE)
	{
		if (isredir(temp->id))
		{
			fd = switch_redir(&temp, data);
			if (fd == INT_MIN || data->utils.exec_status == 130)
				return (1);
			aplly_redirect(fd, temp->id);
		}
		temp = temp->next;
	}
	return (0);
}

void	restore_redirect(int *original, t_data *data)
{
	if (!original || (original[0] < 0 || original[1] < 0))
		return ;
	make_redir(original[0], 0);
	make_redir(original[1], 1);
	destroy_fd(&original);
	data->utils.can_dup = true;
	data->flags.shoud_restore = !data->flags.shoud_restore;
}
