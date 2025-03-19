/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-manage_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:38:03 by jonas             #+#    #+#             */
/*   Updated: 2025/03/19 12:34:11 by jonas            ###   ########.fr       */
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

static t_token	*get_pos(t_token **token, t_ast *root)
{
	t_token	*temp;

	if (!*token || !root)
		return (NULL);
	// printf("vou pesquisar\n");
	temp = *token;
	while ((temp && temp->next)
			&& (temp->id == PIPE || temp->index != root->index))
		temp = temp->next;
	while (temp && temp->previous && temp->id != PIPE)
		temp = temp->previous;
	if (temp->id == PIPE)
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

	// printf("cheguei na manage\n");
	if (!*token || !data || !*root || !isredir((*root)->id))
		return (0);
	// printf("a manage aprovou\n");
	// printf("recebi: %s(%d)\n", (*root)->cmd[0], (*root)->index);
	temp = get_pos(token, find_cmd(root));
	// printf("vou começar a partir daqui %s(%d)\n", temp->str, temp->index);
	fd = -1;
	while (temp && temp->id != PIPE)
	{
		if (isredir(temp->id))
		{
			// printf("vou redirecionar\n");
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
	data->utils.can_read = true;
	data->utils.can_write = true;
	data->flags.shoud_restore = !data->flags.shoud_restore;
}
