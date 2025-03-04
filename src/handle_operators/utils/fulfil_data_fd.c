/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fulfil_data_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:49:24 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/23 14:00:08 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	fulfil_data_fd(int *pipefd, t_utils *data)
{
	close(data->fd_backup);
	data->fd_backup = dup(pipefd[0]);
}
