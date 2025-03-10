/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:05:17 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/10 14:15:40 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_read_mode(char **cmd, int *pipefd, t_data *data)
{
	char	*path;

	if (data->utils.fd_backup < 0)
		exit(EXIT_FAILURE);
	if (dup2(data->utils.fd_backup, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close_descriptors(pipefd, 1, data);
	if (access(cmd[0], F_OK | X_OK))
	{
		path = find_path(cmd[0], data->utils.envp);
		if (!path)
		{
			clear_everything(data, 1);
			exit(errno);
		}
	}
	else
		path = cmd[0];
	execve(path, cmd, data->utils.envp);
	perror("Error: ");
	free(path);
	exit(errno);
}
