/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:45:01 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/25 10:22:23 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_mode(char **cmd, int *pipefd, t_utils *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		close_descriptors(pipefd, 1, data);
		exit(EXIT_FAILURE);
	}
	if (data->fd_backup < 0)
		exit(EXIT_FAILURE);
	if (dup2(data->fd_backup, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (execve(cmd[0], cmd, data->envp) == -1)
	{
		free_splits(NULL, cmd, NULL, NULL);
		exit(errno);
	}
	free_splits(NULL, cmd, NULL, NULL);
	waitpid(pid, &data->exec_status, 0);
}

void	write_mode(char **cmd, int *pipefd, t_utils *data)
{
	int	pid;

	data->fd_backup = dup(pipefd[0]);
	pid = fork();
	if (pid == -1)
	{
		close_descriptors(pipefd, 1, data);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (execve(cmd[0], cmd, data->envp) == -1)
	{
		free_splits(NULL, cmd, NULL, NULL);
		exit(errno);
	}
	free_splits(NULL, cmd, NULL, NULL);
	waitpid(pid, &data->exec_status, 0);
}

int	write_read_mode(char **cmd, int *pipefd, t_utils *data)
{
	if (data->fd_backup < 0)
		return (0);
	if (dup2(data->fd_backup, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	fulfil_data_fd(pipefd, data);
	close_descriptors(pipefd, 1, data);
	if (execve(cmd[0], cmd, data->envp) == -1)
	{
		free_splits(NULL, cmd, NULL, NULL);
		exit(errno);
	}
	free_splits(NULL, cmd, NULL, NULL);
	return (1);
}

int	handle_pipe_op(char *cmd, int flag, t_utils *data)
{
	int		pipefd[2];
	char	**split1;

	if (pipe(pipefd) == -1)
		return (1);
	split1 = ft_split(cmd, ' ');
	if (!split1)
	{
		close_descriptors(pipefd, 1, data);
		return (0);
	}
	if (flag == 1)
		write_mode(split1, pipefd, data);
	else if (flag == 2)
		read_mode(split1, pipefd, data);
	else if (flag == 3)
		write_read_mode(split1, pipefd, data);
	if (flag == 3 || flag == 1)
		close_descriptors(pipefd, 0, data);
	if (flag == 2)
		close_descriptors(pipefd, 1, data);
	return (data->exec_status);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.utils.exec_status = 0;
	(void)argc;
	data.utils.envp = envp;
	if (!handle_pipe_op(argv[1], 1, &data.utils))
		handle_pipe_op(argv[2], 2, &data.utils);
	wait(0);
	return (0);
}*/
