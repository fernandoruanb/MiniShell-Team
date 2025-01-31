/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lab_1_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:40:10 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/27 10:17:56 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

static size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

static int	close_descriptors(int *pipefd)
{
	close(pipefd[1]);
	close(pipefd[0]);
	return (1);
}

static void	parent_process(char **argv, int *pipefd)
{
	size_t	length;

	length = ft_strlen(argv[1]);
	close(pipefd[0]);
	write(pipefd[1], argv[1], length);
	close(pipefd[1]);
}

static void	child_process(char **argv, int *pipefd)
{
	ssize_t	bytes_read;
	ssize_t	length;
	char	*buffer;

	close(pipefd[1]);
	length = ft_strlen(argv[1]);
	buffer = (char *)malloc(length);
	if (!buffer)
	{
		close(pipefd[0]);
		return ;
	}
	bytes_read = read(pipefd[0], buffer, length);
	close(pipefd[0]);
	if (bytes_read == -1)
	{
		free(buffer);
		return ;
	}
	write(1, buffer, bytes_read);
	write(1, "\n", 1);
	free(buffer);
}

int	main(int argc, char **argv)
{
	int	id;
	int	id2;
	int	pipefd[2];

	if (argc < 2)
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
