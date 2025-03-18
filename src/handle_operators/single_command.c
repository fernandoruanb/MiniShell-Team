/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:36:24 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/18 10:58:48 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	single_command(t_ast **root, t_data *data)
{
	int		pid;

	if (!*root || (*root)->id != CMD)
		return ;
	if (check_is_directory_fd((*root)->cmd[0], &data->utils))
	{
		data->utils.exec_status = 126;
		return ;
	}
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		check_errno((*root)->cmd, &data->utils, data);
	waitpid(pid, &data->utils.exec_status, 0);
	translate(data);
}
