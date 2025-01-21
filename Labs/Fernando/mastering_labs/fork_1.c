/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:37:33 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/21 13:01:14 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	child_lets_action(char *buffer, int *pipefd, int length)
{
	close(pipefd[1]);
	read(pipefd[0], buffer, length);
	buffer[length] = '\0';
	printf("The child received: %s\n", buffer);
}

int	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

int	main(int argc, char **argv)
{
	int		length;
	int		id;
	int		pipefd[2];
	char	*buffer;

	if (argc != 2)
		return (1);
	pipe(pipefd);
	length = ft_strlen(argv[1]);
	buffer = malloc(length + 1);
	if (!buffer)
		return (1);
	id = fork();
	if (id == 0)
		child_lets_action(buffer, pipefd, length);
	else
	{
		close(pipefd[0]);
		write(pipefd[1], argv[1], length);
		printf("The father sent the message: %s\n", argv[1]);
		close(pipefd[1]);
	}
	if (buffer)
		free(buffer);
	return (0);
}
