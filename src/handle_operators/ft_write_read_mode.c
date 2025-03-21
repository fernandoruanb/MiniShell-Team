/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_read_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:39:22 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/21 18:59:07 by fruan-ba         ###   ########.fr       */
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

void	ft_write_read_mode(int *pipefd, t_ast **root, t_data *data)
{
	char	*path;
	t_ast	*ast;

	ast = *root;
	handle_command_signal();
	path = NULL;
	if (data->utils.can_write)
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	if (data->utils.can_read)
		if (dup2(data->utils.fd_backup, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	close_descriptors(pipefd, 1, data);
	path = get_path(data, ast->cmd);
	// if (handle_builtin(ast->cmd, data))
	// {
	// 	ultimate_check(ast, path, pipefd, data);
	// 	free(path);
	// 	clean_process(data);
	// 	exit(data->utils.exec_status);
	// }
	ultimate_check(ast, path, pipefd, data);
	if (!handle_builtin(ast->cmd, data))
		if (execve(path, ast->cmd, data->utils.envp) < 0)
			data->utils.exec_status = errno;
	clean_process(data);
	free(path);
	close_all_fds();
	exit(data->utils.exec_status);
}
