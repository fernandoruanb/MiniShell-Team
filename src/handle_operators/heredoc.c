/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:11:40 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/26 18:27:55 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	free_strs(char *str1, char *str2, int flag)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (flag == 1)
		return (1);
	return (0);
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

static int	execute_heredoc(char *cmd, char *filename, t_utils *data)
{
	char	**split1;
	int		pid;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	split1 = ft_split(cmd, ' ');
	if (!split1)
		return (close_fd(fd, NULL, 0));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close_fd(fd, split1, 0));
	pid = fork();
	if (pid == 0)
	{
		if (execve(split1[0], split1, data->envp) == -1)
		{
			free_splits(NULL, split1, NULL, NULL);
			if (errno == ENOENT)
				exit(127);
			else if (errno == EACCES)
				exit(126);
			else
				exit(errno);
		}
	}
	close(fd);
	waitpid(pid, &data->exec_status, 0);
	return (free_splits(NULL, split1, NULL, NULL));
}

int	heredoc(char *cmd, char *limiter, t_utils *data)
{
	int		fd;
	char	*line;
	char	*filename;

	data->exec_status = 0;
	filename = ft_strjoin("/tmp/", limiter);
	if (!filename)
		return (0);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (free_strs(filename, NULL, 0));
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return (free_strs(filename, NULL, 1));
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		else
			ft_putendl_fd(line, fd);
	}
	close(fd);
	if (execute_heredoc(cmd, filename, data))
		delete_heredoc(filename);
	return (free_strs(filename, NULL, 1));
}

/*int	main(int argc, char **argv, char **envp)
{
	int	status;
	t_data	data;

	data.utils.envp = envp;
	if (argc < 2)
		return (1);
	status = 0;
	heredoc(argv[1], argv[2], &data.utils);
	return (0);
}*/
