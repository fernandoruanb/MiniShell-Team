/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fulfil_data_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:49:24 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/07 17:31:38 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	fulfil_data_fd(int *pipefd, t_data *data)
{
	close(data->utils.fd_backup);
	data->utils.fd_backup = dup(pipefd[0]);
}
