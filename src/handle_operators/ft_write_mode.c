/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:57:28 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/14 15:56:45 by jonas            ###   ########.fr       */
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
	path = get_path(data, cmd);
	if (handle_builtin(cmd, data))
	{
		free(path);
		clean_process(data);
		exit(data->utils.exec_status);
	}
	execve(path, cmd, data->utils.envp);
	free(path);
	clean_process(data);
	exit(errno);
}
