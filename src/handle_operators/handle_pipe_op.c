/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:45:01 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/03 17:19:55 by fruan-ba         ###   ########.fr       */
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
	if (pid == 0)
		ft_read_mode(cmd, pipefd, data);
	close_descriptors(pipefd, 1, data);
	free_splits(NULL, cmd, NULL, NULL);
	data->pids[data->index++] = pid;
	data->num_of_processes++;
}

void	write_mode(char **cmd, int *pipefd, t_utils *data)
{
	int	pid;

	data->fd_backup = dup(pipefd[0]);
	if (data->fd_backup == -1)
		return (close_descriptors(pipefd, 0, data));
	pid = fork();
	if (pid == -1)
	{
		close_descriptors(pipefd, 1, data);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		ft_write_mode(pipefd, cmd, data);
	free_splits(NULL, cmd, NULL, NULL);
	data->pid = pid;
	data->pids[data->index++] = pid;
	data->num_of_processes++;
}

void	write_read_mode(char **cmd, int *pipefd, t_utils *data)
{
	int	pid;
	int	fd;

	if (data->fd_backup < 0)
		return (close_descriptors(pipefd, 1, data));
	fd = dup(pipefd[0]);
	if (fd == -1)
		return (close_descriptors(pipefd, 1, data));
	pid = fork();
	if (pid == -1)
	{
		close_descriptors(pipefd, 1, data);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd);
		ft_write_read_mode(pipefd, cmd, data);
	}
	if (data->fd_backup)
		close(data->fd_backup);
	data->fd_backup = fd;
	free_splits(NULL, cmd, NULL, NULL);
	data->pids[data->index++] = pid;
	data->num_of_processes++;
}

void	wait_all_pids(t_utils *data)
{
	int	index;

	index = 0;
	while (index < data->num_of_processes - 1)
	{
		waitpid(data->pids[index], NULL, 0);
		index++;
	}
	waitpid(data->pids[index], &data->exec_status, 0);
	translate(data);
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
		return (1);
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
	if (flag == 2)
		wait_all_pids(data);
	return (data->exec_status);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		index;

	if (argc < 2)
		return (1);
	data.utils.num_of_processes = 0;
	data.utils.exec_status = 0;
	data.utils.index = 0;
	(void)argc;
	data.utils.envp = envp;
	index = 1;
	handle_pipe_op(argv[index], 1, &data.utils);
	index++;
	while (index < argc - 1)
	{
		handle_pipe_op(argv[index], 3, &data.utils);
		index++;
	}
	handle_pipe_op(argv[argc - 1], 2, &data.utils);
	translate(&data.utils);
	printf("EXEC STATUS: %d\n", data.utils.exec_status);
	return (0);
}*/
