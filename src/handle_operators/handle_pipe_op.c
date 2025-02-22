/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:45:01 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/22 20:23:20 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_mode(char **cmd, int *pipefd, t_utils *data)
{
	int		pid;

	if (dup2(data->fd_backup, STDIN_FILENO) == -1)
	{
		close_descriptors(pipefd, 1, data);
		return ;
	}
	close_descriptors(pipefd, 1, data);
	pid = fork();
	if (pid == 0)
	{
		close_descriptors(pipefd, 1, data);
		if (execve(cmd[0], cmd, data->envp) == -1)
		{
			free_splits(NULL, cmd, NULL, NULL);
			exit(errno);
		}
	}
	free_splits(NULL, cmd, NULL, NULL);
	waitpid(pid, &data->exec_status, 0);
}

void	write_mode(char **cmd, int *pipefd, t_utils *data)
{
	int		pid;

	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close_descriptors(pipefd, 0, data);
		return ;
	}
	data->fd_backup = dup(pipefd[0]);
	close_descriptors(pipefd, 0, data);
	pid = fork();
	if (pid == 0)
	{
		close_descriptors(pipefd, 0, data);
		if (execve(cmd[0], cmd, data->envp) == -1)
		{
			free_splits(NULL, cmd, NULL, NULL);
			exit(errno);
		}
	}
	free_splits(NULL, cmd, NULL, NULL);
	waitpid(pid, &data->exec_status, 0);
}

void	write_read_mode(char **cmd, int *pipefd, t_utils *data)
{
	int	pid;

	if (dup2(data->fd_backup, STDIN_FILENO) == -1)
	{
		close_descriptors(pipefd, 1, data);
		return ;
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close_descriptors(pipefd, 1, data);
		return ;
	}
	fulfil_data_fd(pipefd, data);
	pid = fork();
	if (pid == 0)
	{
		close_descriptors(pipefd, 0, data);
		if (execve(cmd[0], cmd, data->envp) == -1)
		{
			free_splits(NULL, cmd, NULL, NULL);
			exit(errno);
		}
	}
	free_splits(NULL, cmd, NULL, NULL);
	waitpid(pid, &data->exec_status, 0);
}

int	handle_pipe_op(char *cmd, int flag, t_utils *data)
{
	int		pipefd[2];
	char	**split1;

	if (pipe(pipefd) == -1)
		return (0);
	split1 = ft_split(cmd, ' ');
	if (!split1)
	{
		close_descriptors(pipefd, 0, data);
		return (0);
	}
	if (flag == 1)
		write_mode(split1, pipefd, data);
	else if (flag == 2)
		read_mode(split1, pipefd, data);
	else if (flag == 3)
		write_read_mode(split1, pipefd, data);
	return (1);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.utils.envp = envp;
	if (handle_pipe_op(argv[1], 1, &data.utils))
		handle_pipe_op(argv[2], 2, &data.utils);
	return (0);
}*/
