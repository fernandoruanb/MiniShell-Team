/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-manage_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:38:03 by jonas             #+#    #+#             */
/*   Updated: 2025/03/20 20:15:17 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	aplly_redirect(int fd, t_id id)
{
	int	std;

	if (fd < 0)
		return ;
	std = (id == REDIRECT_OUT || id == APPEND);
	make_redir(fd, std);
	close (fd);
}

int	redir_out(char *name, t_id id, t_data *data)
{
	int	fd;

	fd = -1;
	if (id == REDIRECT_OUT)
		fd = handle_redirect_out(name, &data->utils);
	else if (id == APPEND)
		fd = append(name, &data->utils);
	if (fd >= 0)
		data->utils.can_write = false;
	return (fd);
}

int	redir_in(char *name, t_id id, t_token **token, t_data *data)
{
	int	fd;

	fd = -1;
	if (id == REDIRECT_IN)
		fd = handle_red_in(name, &data->utils);
	else if (id == HEREDOC)
		fd = heredoc(name, data, token);
	if (fd >= 0)
		data->utils.can_read = false;
	return (fd);
}

static t_token	*get_pos(t_token **token, t_ast *root)
{
	t_token	*temp;

	if (!*token || !root)
		return (NULL);
	temp = *token;
	while (temp
		&& temp->next
		&& (temp->id == PIPE || temp->index != root->index))
		temp = temp->next;
	while (temp && temp->previous && temp->id != PIPE)
		temp = temp->previous;
	if (temp->id == PIPE)
		temp = temp->next;
	return (temp);
}

t_ast	*find_cmd2(t_ast **root)
{
	if (isredir((*root)->id))
		return (*root);
	return (find_cmd(root));
}

int	manage_redir(t_ast **root, t_token **token, t_data *data)
{
	int		fd;
	t_token	*temp;

	if (!*token || !data || !*root || !isredir((*root)->id))
		return (0);
	temp = get_pos(token, find_cmd2(root));
	fd = -1;
	// printf("chaguei na manage\n");
	while (temp && temp->id != PIPE)
	{
		if (isredir(temp->id))
		{
			// printf("vou fazer redirect\n");
			fd = switch_redir(&temp, data);
			if (fd == INT_MIN || data->utils.exec_status == 130)
				return (1);
			aplly_redirect(fd, temp->id);
		}
		temp = temp->next;
	}
	return (0);
}
