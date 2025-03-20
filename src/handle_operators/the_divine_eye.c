/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_divine_eye.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:14:22 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/20 12:14:22 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	the_divine_eye(int *pipefd, t_ast **root, t_data *data)
{
	if (data->utils.fd_backup < 0)
		close_descriptors(pipefd, 1, data);
	if (check_is_directory_fd((*root)->cmd[0], &data->utils))
	{
		data->utils.exec_status = 126;
		close_descriptors(pipefd, 0, data);
		return ;
	}
}
