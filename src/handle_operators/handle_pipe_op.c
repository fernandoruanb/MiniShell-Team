/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:45:01 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/21 16:04:52 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_descriptors(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	read_mode(char **cmd, int *pipefd, char **envp, int *status)
{
	int		pid;

	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close_descriptors(pipefd);
		return ;
	}
	close_descriptors(pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
		{
			free_splits(NULL, cmd, NULL, NULL);
			exit(errno);
		}
	}
	free_splits(NULL, cmd, NULL, NULL);
	waitpid(pid, status, 0);
}

void	write_mode(char **cmd, int *pipefd, char **envp, int *status)
{
	int		pid;

	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close_descriptors(pipefd);
		return ;
	}
	close_descriptors(pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
		{
			free_splits(NULL, cmd, NULL, NULL);
			exit(errno);
		}
	}
	free_splits(NULL, cmd, NULL, NULL);
	waitpid(pid, status, 0);
}

void	write_read_mode(char **cmd, int *pipefd, char **envp, int *status)
{
	int	pid;

	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close_descriptors(pipefd);
		return ;
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close_descriptors(pipefd);
		return ;
	}
	close_descriptors(pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
		{
			free_splits(NULL, cmd, NULL, NULL);
			exit(errno);
		}
	}
	free_splits(NULL, cmd, NULL, NULL);
	waitpid(pid, status, 0);
}

int	handle_pipe_op(char *cmd, int flag, char **envp)
{
	int		pipefd[2];
	char	**split1;
	int		status;

	if (pipe(pipefd) == -1)
		return (0);
	status = 0;
	split1 = ft_split(cmd, ' ');
	if (!split1)
		return (0);
	if (flag == 1)
		write_mode(split1, pipefd, envp, &status);
	else if (flag == 2)
		read_mode(split1, pipefd, envp, &status);
	else if (flag == 3)
		write_read_mode(split1, pipefd, envp, &status);
	return (1);
}

/*int	main(int argc, char **argv, char **envp)
{
	return (0);
}*/
