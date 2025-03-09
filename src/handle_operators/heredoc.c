/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:11:40 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/08 20:24:00 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	free_strs(char *str1, char *str2, int flag)
{
	free(str1);
	free(str2);
	return (flag);
}

static int	close_fd(int fd, char **split1, int flag)
{
	close(fd);
	if (split1)
		free_splits(NULL, split1, NULL, NULL);
	if (flag == 1)
		return (1);
	return (0);
}

static void	delete_heredoc(char *filename)
{
	int		pid;
	char	*target;
	char	**split2;

	target = ft_strjoin("/bin/rm -- ", filename);
	if (!target)
		return ;
	split2 = ft_split(target, ' ');
	if (!split2)
	{
		free(target);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve("/bin/rm", split2, NULL) == -1)
		{
			free_splits(target, split2, NULL, NULL);
			exit(errno);
		}
	}
	free_splits(target, split2, NULL, NULL);
	waitpid(pid, NULL, 0);
}

static int	execute_heredoc(char **cmd, char *filename, t_utils *data)
{
	int		pid;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close_fd(fd, NULL, 0));
	pid = fork();
	if (pid == 0)
		check_errno(cmd, data);
	close(fd);
	waitpid(pid, &data->exec_status, 0);
	return (free_splits(NULL, cmd, NULL, NULL));
}

int	heredoc(char **cmd, char *limiter, t_utils *data, int flag)
{
	int		fd;
	char	*line;
	char	*filename;

	line = NULL;
	data->exec_status = 0;
	filename = ft_strjoin("/tmp/", limiter);
	if (!filename)
		return (0);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (free_strs(filename, NULL, 0));
	heredoc_check_mode(line, limiter, fd);
	close(fd);
	if (flag == 1)
		execute_heredoc(cmd, filename, data);
	delete_heredoc(filename);
	free(filename);
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