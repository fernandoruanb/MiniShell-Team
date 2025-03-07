/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:57:28 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/07 17:57:28 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_write_mode(int *pipefd, char **cmd, t_data *data)
{
	char	*path;

	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close_descriptors(pipefd, 1, data);
	if (handle_builtin(cmd, data))
		return ;
	if (access(cmd[0], F_OK | X_OK))
		path = find_path(cmd[0], data->utils.envp);
	else
		path = cmd[0];
	if (path)
		execve(path, cmd, data->utils.envp);
	free(path);
	perror("Error: ");
	//free_splits(NULL, cmd, NULL, NULL);
	exit(errno);
}
