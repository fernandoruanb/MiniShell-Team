/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:51:23 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/14 12:51:25 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <fcntl.h>
#include <unistd.h>

/*void	ft_putendl_fd(char *s, int fd);

int	main(int argc, char **argv)
{
	int	file_descriptor;

	if (argc < 2)
	{
		write(1, "File name missing.\n", 19);
		return (1);
	}
	if (argc > 3)
	{
		write(1, "Too many arguments.\n", 20);
		return (1);
	}
	file_descriptor = open(argv[1], O_WRONLY | O_APPEND);
	if (file_descriptor == -1)
		return (1);
	ft_putendl_fd(argv[2], file_descriptor);
	close(file_descriptor);
	return (0);
}*/

void	ft_putendl_fd(char *s, int fd)
{
	int	index;

	if (!s || fd == -1)
		return ;
	index = 0;
	while (s[index] != '\0')
	{
		write(fd, &s[index], 1);
		index++;
	}
	write(fd, "\n", 1);
}
