/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:05:17 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/11 18:42:25 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_read_mode(char **cmd, int *pipefd, t_data *data)
{
	char	*path;

	path = NULL;
	if (data->utils.fd_backup < 0)
		exit(EXIT_FAILURE);
	if (dup2(data->utils.fd_backup, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close_descriptors(pipefd, 1, data);
	if (!isbuiltin(cmd[0]) && access(cmd[0], F_OK | X_OK))
	{
		path = find_path(cmd[0], data->utils.envp, data);
		if (!path)
		{
			clean_process(data);
			exit(127);
		}
	}
	else
		path = cmd[0];
	if (!handle_builtin(cmd, data))
		execve(path, cmd, data->utils.envp);
	clean_process(data);
	free(path);
	//perror("Error: ");
	exit(errno);
}
