/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:57:28 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/13 14:09:02 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_write_mode(int *pipefd, char **cmd, t_data *data)
{
	char	*path;

	handle_command_signal();
	path = NULL;
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close_descriptors(pipefd, 1, data);
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
		path = cmd[0];
	if (!handle_builtin(cmd, data))
		execve(path, cmd, data->utils.envp);
	clean_process(data);
	exit(errno);
} 	
