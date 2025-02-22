/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fulfil_data_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:11:17 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/22 20:11:32 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	fulfil_data_fd(int *pipefd, t_utils *data)
{
	close(data->fd_backup);
	data->fd_backup = dup(pipefd[0]);
	close_descriptors(pipefd, 0, data);
}
