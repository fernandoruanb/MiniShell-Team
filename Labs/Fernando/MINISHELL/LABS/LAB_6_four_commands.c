/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LAB_6_four_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:23:49 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/27 15:21:51 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

static int	close_descriptors(int *pipefd, int *pipefd2, int *pipefd3)
{
	if (pipefd != NULL)
	{
		close(pipefd[1]);
		close(pipefd[0]);
	}
	if (pipefd2 != NULL)
	{
		close(pipefd2[0]);
		close(pipefd2[1]);
	}
	if (pipefd3 != NULL)
	{
		close(pipefd3[0]);
		close(pipefd3[1]);
	}
	return (1);
}

static void	forth_command(char **argv, int *pipefd, int *pipefd2, int *pipefd3)
{
	char	*args[3];

	close(pipefd3[1]);
	close_descriptors(pipefd, pipefd2, NULL);
	if (dup2(pipefd3[0], STDIN_FILENO) == -1)
	{
		close(pipefd3[0]);
		return ;
	}
	close(pipefd3[0]);
	args[0] = argv[7];
	args[1] = argv[8];
	args[2] = NULL;
	if (execve(args[0], args, NULL) == -1)
	{
		printf("Error executing forth command.\n");
		exit(EXIT_FAILURE);
	}
}

static void	third_command(char **argv, int *pipefd, int *pipefd2, int *pipefd3)
{
	char	*args[3];

	close(pipefd2[1]);
	close(pipefd3[0]);
	close_descriptors(pipefd, NULL, NULL);
	if (dup2(pipefd2[0], STDIN_FILENO) == -1)
	{
		close(pipefd2[0]);
		close(pipefd3[1]);
		return ;
	}
	if (dup2(pipefd3[1], STDOUT_FILENO) == -1)
	{
		close(pipefd2[0]);
		close(pipefd3[1]);
		return ;
	}
	close(pipefd2[0]);
	close(pipefd3[1]);
	args[0] = argv[5];
	args[1] = argv[6];
	args[2] = NULL;
	if (execve(args[0], args, NULL) != -1)
	{
		printf("Error executing the third command.\n");
		exit(EXIT_FAILURE);
	}
}

static void	second_command(char **argv, int *pipefd, int *pipefd2)
{
	char	*args[3];

	close(pipefd[1]);
	close(pipefd2[0]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		close(pipefd2[1]);
		return ;
	}
	if (dup2(pipefd2[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[0]);
		close(pipefd2[1]);
		return ;
	}
	close(pipefd[0]);
	close(pipefd2[1]);
	args[0] = argv[3];
	args[1] = argv[4];
	args[2] = NULL;
	if (execve(args[0], args, NULL) == -1)
	{
		printf("Error executing the second command.\n");
		exit(EXIT_FAILURE);
	}
}

static void	first_command(char **argv, int *pipefd)
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
		printf("Error executing first command.\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	int	id;
	int	id1;
	int	id2;
	int	id3;
	int	pipefd[2];
	int	pipefd2[2];
	int	pipefd3[2];

	if (argc != 9)
		return (1);
	if (pipe(pipefd) == -1)
		return (1);
	if (pipe(pipefd2) == -1)
		return (close_descriptors(pipefd, NULL, NULL));
	if (pipe(pipefd3) == -1)
		return (close_descriptors(pipefd, pipefd2, NULL));
	id = fork();
	if (id == -1)
		return (close_descriptors(pipefd, pipefd2, pipefd3));
	if (id == 0)
		first_command(argv, pipefd);
	id1 = fork();
	if (id1 == -1)
		return (close_descriptors(pipefd, pipefd2, pipefd3));
	if (id1 == 0)
		second_command(argv, pipefd, pipefd2);
	id2 = fork();
	if (id2 == -1)
		return (close_descriptors(pipefd, pipefd2, pipefd3));
	if (id2 == 0)
		third_command(argv, pipefd, pipefd2, pipefd3);
	id3 = fork();
	if (id3 == -1)
		return (close_descriptors(pipefd, pipefd2, pipefd3));
	if (id3 == 0)
		forth_command(argv, pipefd, pipefd2, pipefd3);
	close_descriptors(pipefd, pipefd2, pipefd3);
	waitpid(id, NULL, 0);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
	waitpid(id3, NULL, 0);
	return (0);
}
