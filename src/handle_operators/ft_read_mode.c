/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:05:17 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/05 12:58:03 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_read_mode(char **cmd, int *pipefd, t_utils *data)
{
	char	*path;

	if (data->fd_backup < 0)
		exit(EXIT_FAILURE);
	if (dup2(data->fd_backup, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close_descriptors(pipefd, 1, data);
	if (access(cmd[0], F_OK | X_OK))
		path = find_path(cmd[0], data->envp);
	else
		path = cmd[0];
	if (path)
		execve(path, cmd, data->envp);
	perror("Error: ");
	free(path);
	//free_splits(NULL, cmd, NULL, NULL);
	exit(errno);
}
 