/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_descriptors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:10:36 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/24 15:12:43 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	close_descriptors(int *pipefd, int *pipefd2)
{
	if (pipefd)
	{
		close(pipefd[1]);
		close(pipefd[0]);
	}
	if (pipefd2)
	{
		close(pipefd2[1]);
		close(pipefd2[0]);
	}
	return (1);
}
