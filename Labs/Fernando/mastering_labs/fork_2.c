/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:05:30 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/21 14:15:03 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void	child_process_action(char *b, int *p1, int *p2, int l)
{
	int	bytes_read;

	if (!b)
		return ;
	close(p1[1]);
	close(p2[0]);
	bytes_read = read(p1[0], b, l);
	if (bytes_read == -1)
	{
		printf("The child failed to receive the message.\n");
		return ;
	}
	printf("The child received: %s\n", b);
	write(p2[1], "I got the message.", 18);
	close(p2[1]);
}

static void	parent_process_action(char *s, int *p1, int *p2, int l)
{
	int		bytes_read;
	char	buffer[100];

	if (!s)
		return ;
	close(p1[0]);
	close(p2[1]);
	write(p1[1], s, l);
	printf("The father sent a message: %s\n", s);
	bytes_read = read(p2[0], buffer, sizeof(buffer));
	if (bytes_read == -1)
	{
		printf("Failed to receive a good answer from child.\n");
		return ;
	}
	buffer[bytes_read] = '\0';
	printf("The father received the answer: %s\n", buffer);
	close(p1[1]);
}

static int	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

int	main(int argc, char **argv)
{
	int		pipe1[2];
	int		pipe2[2];
	int		id;
	int		length;
	char	*buffer;

	if (argc != 2)
		return (1);
	if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
		return (1);
	length = ft_strlen(argv[1]);
	buffer = malloc(length + 1);
	if (!buffer)
		return (1);
	buffer[length] = '\0';
	id = fork();
	if (id == -1)
		return (1);
	if (id == 0)
		child_process_action(buffer, pipe1, pipe2, length);
	else
		parent_process_action(argv[1], pipe1, pipe2, length);
	if (buffer)
		free(buffer);
	return (0);
}
