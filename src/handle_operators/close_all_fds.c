/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:42:53 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/22 15:49:37 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_all_fds(void)
{
	long	fd;
	long	index;

	index = 3;
	while (1)
	{
		fd = dup(index);
		if (fd != -1)
		{
			close(fd);
			close(index);
		}
		else
			break ;
		index++;
	}
}
