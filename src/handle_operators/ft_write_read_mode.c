/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_read_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:39:22 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/10 16:56:24 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_write_read_mode(int *pipefd, char **cmd, t_data *data)
{
	char	*path;

	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(data->utils.fd_backup, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close_descriptors(pipefd, 1, data);
	if (access(cmd[0], F_OK | X_OK))
	{
		path = find_path(cmd[0], data->utils.envp, data);
		if (!path)
			exit(errno);
	}
	else
		path = cmd[0];
	if (!handle_builtin(cmd, data))
		execve(path, cmd, data->utils.envp);
	call_clean(data);
	free(path);
	perror("Error: ");
	exit(errno);
}
