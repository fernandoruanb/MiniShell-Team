/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:05:17 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/26 13:34:36 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_read_mode(char **cmd, t_utils *data)
{
	if (data->fd_backup < 0)
		exit(EXIT_FAILURE);
	if (dup2(data->fd_backup, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (execve(cmd[0], cmd, data->envp) == -1)
	{
		perror("CMD Error read_mode\n");
		free_splits(NULL, cmd, NULL, NULL);
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES)
			exit(126);
		else
			exit(errno);
	}
}
