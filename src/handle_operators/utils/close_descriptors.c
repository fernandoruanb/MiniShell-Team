/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_descriptors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:51:18 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/23 11:52:02 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	close_descriptors(int *pipefd, int flag, t_utils *data)
{
	close(pipefd[0]);
	close(pipefd[1]);
	if (flag == 1)
		close(data->fd_backup);
}
