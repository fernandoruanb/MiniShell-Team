/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:05:05 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/21 16:11:37 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	append(char *message, char *filename)
{
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	ft_putendl_fd(message, fd);
	if (fd > 2)
		close(fd);
}

/*int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	append(argv[1], argv[2]);
	return (0);
}*/
