/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LAB_4_exec_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:21:51 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/27 13:01:59 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

static int	close_descriptors(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	return (1);
}

static void	parent_process(char **argv, int *pipefd)
{
	char	*args[3];

	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		return ;
	}
	close(pipefd[0]);
	args[0] = argv[3];
	args[1] = argv[4];
	args[2] = NULL;
	if (execve(args[0], args, NULL) == -1)
	{
		printf("Failed executing second command.\n");
		exit(EXIT_FAILURE);
	}
}

static void	child_process(char **argv, int *pipefd)
{
	char	*args[3];

	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[1]);
		return ;
	}
	close(pipefd[1]);
	args[0] = argv[1];
	args[1] = argv[2];
	args[2] = NULL;
	if (execve(args[0], args, NULL) == -1)
	{
		printf("Error executing the first command!");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	int	id;
	int	id2;
	int	pipefd[2];

	if (argc != 5)
		return (1);
	if (pipe(pipefd) == -1)
		return (1);
	id = fork();
	if (id == -1)
		return (close_descriptors(pipefd));
	if (id == 0)
		child_process(argv, pipefd);
	id2 = fork();
	if (id2 == -1)
		return (close_descriptors(pipefd));
	if (id2 == 0)
		parent_process(argv, pipefd);
	close_descriptors(pipefd);
	waitpid(id, NULL, 0);
	waitpid(id2, NULL, 0);
	return (0);
}
