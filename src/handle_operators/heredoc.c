/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:11:40 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/13 17:07:27 by jonas            ###   ########.fr       */
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
static int	heredoc_count(t_token **token)
{
	t_token	*temp;
	int		i;

	if (!*token)
		return (0);
	i = -1;
	temp = *token;
	while (temp)
	{
		if (temp->id == HEREDOC)
			i = temp->index;
		temp = temp->next;
	}
	return (i);
}

int	heredoc(char *limiter, t_data *data, int index)
{
	int		fd;
	int		last;
	pid_t	pid;

	last = heredoc_count(&data->token);
	printf("last: %d index: %d\n", last, index);
	data->utils.exec_status = 0;
	data->utils.filename = ft_strjoin("/tmp/", limiter);
	if (!data->utils.filename)
		return (-1);
	fd = open(data->utils.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (index == last)
	{
		pid = fork();
		if (!pid)
			heredoc_check_mode(&data->utils, limiter, &fd);
		waitpid(pid, &data->utils.exec_status, 0);
	}
	else
		close (fd);
	free(data->utils.filename);
	return (fd);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	**cmd;
	int	index;

	data.utils.exec_status = 0;
	data.utils.envp = envp;
	(void)argc;
	cmd = ft_split(argv[1], ' ');
	if (!cmd)
		return (1);
	index = 2;
	while (index < argc - 1)
	{
		heredoc(cmd, argv[index], &data.utils, 0);
		index++;
	}
	heredoc(cmd, argv[index], &data.utils, 1);
	translate(&data);
	return (0);
}*/
