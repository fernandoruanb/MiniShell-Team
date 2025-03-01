/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:45:01 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/01 20:02:30 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//void    get_not_canonical_mode(struct termios *original);

//void    get_canonical_mode(struct termios *original);

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
		ft_read_mode(cmd, data);
	free_splits(NULL, cmd, NULL, NULL);
	waitpid(pid, &data->exec_status, 0);
}

/*void	get_canonical_mode(struct termios *original)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, original) == -1)
	{
		perror("Error setting original mode");
		exit(1);
	}
}

void	get_not_canonical_mode(struct termios *original)
{
	struct termios temp;

	if (tcgetattr(STDIN_FILENO, original) == -1)
	{
		perror("Error getting information about terminal");
		exit(1);
	}
	temp = *original;
	temp.c_lflag &= ~(ICANON | ECHO);
	temp.c_cc[VMIN] = 1;
	temp.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &temp) == -1)
	{
		perror("Error setting not canonical mode");
		exit(1);
	}
}*/

int	write_mode(char **cmd, int *pipefd, t_utils *data)
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
	return (1);
}

int	write_read_mode(char **cmd, int *pipefd, t_utils *data)
{
	int	pid;
	int	fd;

	if (data->fd_backup < 0)
		return (close_descriptors(pipefd, 0, data));
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
		ft_write_read_mode(pipefd, cmd, data);
	close(data->fd_backup);
	data->fd_backup = fd;
	free_splits(NULL, cmd, NULL, NULL);
	data->pid = pid;
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
	return (data->exec_status);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		index;
	int		count;
	int		pid[9000];
	int		old;
	int		temp;

	if (argc < 2)
		return (1);
	data.utils.exec_status = 0;
	index = 1;
	count = 0;
	(void)argc;
	data.utils.envp = envp;
	handle_pipe_op(argv[index], 1, &data.utils);
	pid[count] = data.utils.pid;
	count++;
	index++;
	while (index < argc - 1)
	{
		handle_pipe_op(argv[index], 3, &data.utils);
		pid[count] = data.utils.pid;
		count++;
		index++;
	}
	handle_pipe_op(argv[argc - 1], 2, &data.utils);
	pid[count] = data.utils.pid;
	count++;
	translate(&data.utils);
	if (data.utils.exec_status == 13)
		data.utils.exec_status = temp;
	translate(&data.utils);
	printf("EXEC STATUS: %d\n", data.utils.exec_status);
	return (0);
}*/
