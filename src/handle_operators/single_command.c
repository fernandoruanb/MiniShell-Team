/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:36:24 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/06 15:16:52 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	single_command(char **cmd, t_utils *data, int *fd)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		check_errno(cmd, data);
	waitpid(pid, &data->exec_status, 0);
	restore_redirect(fd);
}
