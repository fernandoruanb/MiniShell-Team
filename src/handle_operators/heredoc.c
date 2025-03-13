/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:11:40 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/13 19:30:05 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static int	free_strs(char *str1, char *str2)
// {
// 	free(str1);
// 	free(str2);
// 	return (-1);
// }

// static void	close_fd(int fd)
// {
// 	close(fd);
// }

// static void	delete_heredoc(char *filename)
// {
// 	int		pid;
// 	char	*target;
// 	char	**split2;

// 	target = ft_strjoin("/bin/rm -- ", filename);
// 	if (!target)
// 		return ;
// 	split2 = ft_split(target, ' ');
// 	if (!split2)
// 	{
// 		free(target);
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (execve("/bin/rm", split2, NULL) == -1)
// 		{
// 			free_splits(target, split2, NULL, NULL);
// 			exit(errno);
// 		}
// 	}
// 	free_splits(target, split2, NULL, NULL);
// 	waitpid(pid, NULL, 0);
// }

// static void	execute_heredoc(char **cmd, char *filename, t_data *data)
// {
// 	int		pid;
// 	int		fd;

// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		return ;
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 		return (close_fd(fd));
// 	pid = fork();
// 	if (pid == 0)
// 		check_errno(cmd, &data->utils, data);
// 	close(fd);
// 	waitpid(pid, &data->utils.exec_status, 0);
// }

/*
	get the index of the last heredoc
*/
// static int	heredoc_count(t_token **token)
// {
// 	t_token	*temp;
// 	int		i;

// 	if (!*token)
// 		return (0);
// 	i = -1;
// 	temp = *token;
// 	while (temp)
// 	{
// 		if (temp->id == HEREDOC)
// 			i = temp->index;
// 		temp = temp->next;
// 	}
// 	return (i);
// }

static int	open_heredoc(t_data *data, int index)
{
	int		fd;
	char	*filename;

	filename = ft_itoa(index);
	if (!filename)
		return (-1);
	data->utils.filename = ft_strjoin("/tmp/", filename);
	free(filename);
	if (!data->utils.filename)
		return (-1);
	fd = open(data->utils.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

static void	open_fork(t_data *data, char *limiter, int *fd)
{
	pid_t	pid;

	if (*fd < 0)
		return ;
	pid = fork();
	if (!pid)
		heredoc_check_mode(data, limiter, fd);
	waitpid(pid, &data->utils.exec_status, 0);
	translate(data);
	close (*fd);
}

/*
	Return the last heredoc index or -1 if its not found
*/
static int	get_last_index(t_token **token)
{
	t_token	*temp;
	int		last;

	if (!*token)
		return (-1);
	last = -1;
	temp = *token;
	while (temp)
	{
		if (temp->id == HEREDOC)
			last = temp->index;
		temp = temp->next;
	}
	return (last);
}

/*
	Open only for the last heredoc

	Open the file was writen by check_mode and returns the id
	to redirect for the command
*/
static int	open_file_to_redirect(t_data *data, t_token **token, int *fd)
{
	int	last;

	last = get_last_index(token);
	printf("token %d last %d\n", (*token)->index, last);
	if ((*token)->index != last)
	{
		free(data->utils.filename);
		return (-1);
	}
	*fd = open (data->utils.filename, O_RDONLY);
	free(data->utils.filename);
	return (*fd);
}

int	heredoc(char *limiter, t_data *data, t_token **token)
{
	int		fd;

	if (!limiter || !data || !*token)
		return (-1);
	printf("token index: %d\n", (*token)->index);
	fd = open_heredoc(data, (*token)->index);
	open_fork(data, limiter, &fd);
	return (open_file_to_redirect(data, token, &fd));
}
