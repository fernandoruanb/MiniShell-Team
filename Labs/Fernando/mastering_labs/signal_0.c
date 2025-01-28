/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:28:49 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/21 19:07:34 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void	handle_signal(int signal)
{
	if (signal == SIGUSR1)
		printf("The child process received SIGUSR1.\n");
	else if (signal == SIGUSR2)
		printf("The child process received SIGUSR2.\n");
}

int	main(void)
{
	int	id;
	int	bytes_read;
	int	pipefd[2];
	char	buffer[2];
	int	count;
	int	child_pid;

	id = fork();
	if (id == -1)
		return (1);
	if (pipe(pipefd) == -1)
		return (1);
	count = 0;
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (!count)
	{
		if (id == 0)
		{
			close(pipefd[0]);
			child_pid = getpid();
			write(pipefd[1], "OK", 2);
			printf("Child process started with PID: %d\n", child_pid);
			close(pipefd[1]);
			count = 1;
			while (1)
				pause();
		}
		else
		{
			close(pipefd[1]);
			child_pid = id;
			bytes_read = read(pipefd[0], buffer, 2);
			if (buffer[0] == 'O' && buffer[1] == 'K')
				printf("Child is ready!\n");
			printf("Parent process sending signals to child: %d\n", child_pid);
			kill(child_pid, SIGUSR1);
			sleep(1);
			kill(child_pid, SIGUSR2);
			sleep(1);
			kill(child_pid, SIGKILL);
		}
	}
	return (0);
}
