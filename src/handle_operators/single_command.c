/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:36:24 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/09 13:55:20 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	single_command(t_ast **root, t_data *data)
{
	int		pid;

	if (!*root || (*root)->id != CMD)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		check_errno((*root)->cmd, &data->utils);
	waitpid(pid, &data->utils.exec_status, 0);
	data->utils.exec_status = (data->utils.exec_status >> 8) & 0xFF;
}
