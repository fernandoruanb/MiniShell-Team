/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:17:01 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/21 12:30:30 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int	pipefd[2];
	int	id;
	char	buffer[2];

	if (pipe(pipefd) == -1)
	{
		printf("Error pipe communication channel.\n");
		return (1);
	}
	id = fork();
	if (id == -1)
	{
		printf("Error creating child process.\n");
		return (1);
	}
	if (id == 0)
	{
		close(pipefd[1]);
		read(pipefd[0], buffer, sizeof(buffer));
		printf("The child received: %s\n", buffer);
	}
	else
	{
		close(pipefd[0]);
		write(pipefd[1], "oi", 2);
		printf("The father process sent the message: 'oi'\n");
		return (pipefd[1]);
	}
	return (0);
}
