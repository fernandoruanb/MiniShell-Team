/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:33:23 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/16 09:41:04 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putendl_fd_0(char *message, int fd)
{
	int	index;

	index = 0;
	while (message[index] != '\0')
	{
		write(fd, &message[index], 1);
		index++;
	}
	write(fd, "\n", 1);
	return (0);
}
