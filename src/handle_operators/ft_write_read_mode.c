/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_read_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:39:22 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/14 15:56:50 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path(t_data *data, char **cmd)
{
	char	*path;

	if (!cmd[0] || cmd[0][0] == '\0')
	{
		clean_process(data);
		exit(0);
	}
	if (!isbuiltin(cmd[0])
		&& (!ft_strnstr(cmd[0], "./", ft_strlen(cmd[0]))
			&& access(cmd[0], F_OK | X_OK)))
	{
		path = find_path(cmd[0], data->utils.envp, data);
		if (!path)
		{
			clean_process(data);
			exit(127);
		}
	}
	else
		path = ft_strdup(cmd[0]);
	return (path);
}

void	ft_write_read_mode(int *pipefd, char **cmd, t_data *data)
{
	char	*path;

	handle_command_signal();
	path = NULL;
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(data->utils.fd_backup, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close_descriptors(pipefd, 1, data);
	path = get_path(data, cmd);
	if (handle_builtin(cmd, data))
	{
		free(path);
		clean_process(data);
		exit(data->utils.exec_status);
	}
	execve(path, cmd, data->utils.envp);
	clean_process(data);
	free(path);
	exit(errno);
}
