/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:57:28 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/11 18:06:57 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_write_mode(int *pipefd, char **cmd, t_data *data)
{
	char	*path;

	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close_descriptors(pipefd, 1, data);
	if (access(cmd[0], F_OK | X_OK))
	{
		path = find_path(cmd[0], data->utils.envp, data);
		if (!path)
		{
			free(data->prompt->input);
			free(data->prompt);
			exit(127);
		}
	}
	else
		path = ft_strdup(cmd[0]);
	if (!handle_builtin(cmd, data))
		execve(path, cmd, data->utils.envp);
	clean_program(&data->utils);
	call_clean(data);
	free(path);
	perror("Error: ");
	exit(errno);
}
