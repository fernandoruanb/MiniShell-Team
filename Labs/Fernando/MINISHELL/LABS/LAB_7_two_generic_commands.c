/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LAB_7_two_generic_commands.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:33:38 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/27 19:24:44 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

static int	close_descriptors(int num_cmds, int *pipefds[2])
{
	int	index;

	index = 0;
	while (index < num_cmds)
	{
		close(pipefds[index][0]);
		close(pipefds[index][1]);
		index++;
	}
	return (1);
}

static int	*create_fork(int num_cmds)
{
	int	pid;
	int	index;
	int	*pids;

	pids = (int *)malloc(num_cmds * sizeof(int));
	if (!pids)
		return (NULL);
	index = 0;
	while (index < num_cmds)
	{
		pid = fork();
		if (pid == -1)
		{
			free(pids);
			return (NULL);
		}
		pids[index] = pid;
		index++;
	}
	return (pids);
}

static int	*create_pipes(int num_cmds)
{
	int	index;
	int	*pipefds[2];

	if (num_cmds <= 0)
		return (NULL);
	pipefds = (int (*)[2])malloc((num_cmds - 1) * sizeof(int[2]));
	if (!pipefds)
		return (NULL);
	index = 0;
	while (index < num_cmds)
	{
		if (pipe(pipefds[index]) == -1)
		{
			index--;
			while (index > 0)
				close_descriptors(pipefds[index--]);
			return (NULL);
		}
		index++;
	}
	return (pipefds);
}

int	main(int argc, char **argv)
{
	int	index;
	int	*pipefds[2];
	int	*pids;
	int	num_cmds;

	num_cmds = (argc - 1) / 2;
	if (num_cmds > 0)
	{
		pipefds = create_pipes(num_cmds);
		if (!pipefds)
			return (1);
		pids = create_forks(num_cmds);
		if (!pids)
			return (close_descriptors(num_cmds, pipefds));
		close_descriptors(num_cmds, pipefds);
	index = 0;
	while (index < num_cmds)
		waitpid(pids[index++], NULL, 0);
	}
	return (0);
}
