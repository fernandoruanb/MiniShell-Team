/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:57:28 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/26 10:16:54 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_write_mode(int *pipefd, char **cmd, t_utils *data)
{
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (execve(cmd[0], cmd, data->envp) == -1)
	{
		perror("CMD Error write_mode\n");
		free_splits(NULL, cmd, NULL, NULL);
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES)
			exit(126);
		exit(errno);
	}
}
