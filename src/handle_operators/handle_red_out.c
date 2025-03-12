/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 08:09:42 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/12 13:17:02 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redirect_out(char *message, char *filename)
{
	int		fd;

	handle_command_signal();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	handle_redirect_out(argv[1], argv[2]);
	return (0);
}*/
