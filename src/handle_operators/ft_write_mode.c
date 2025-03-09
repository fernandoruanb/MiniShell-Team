/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:57:28 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/09 16:44:06 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_write_mode(int *pipefd, char **cmd, t_data *data)
{
	char	*path;

	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (handle_builtin(cmd, data))
		exit(0);
	close_descriptors(pipefd, 1, data);
	if (access(cmd[0], F_OK | X_OK))
		path = find_path(cmd[0], data->utils.envp);
	else
		path = cmd[0];
	if (path)
		execve(path, cmd, data->utils.envp);
	free(path);
	perror("Error: ");
	exit(errno);
}
