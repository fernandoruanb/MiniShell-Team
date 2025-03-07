/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_descriptors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:51:18 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/07 17:31:20 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	close_descriptors(int *pipefd, int flag, t_data *data)
{
	close(pipefd[0]);
	close(pipefd[1]);
	if (flag == 1 && data->utils.fd_backup)
		close(data->utils.fd_backup);
	return (1);
}
