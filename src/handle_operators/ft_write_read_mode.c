/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_read_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:39:22 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/17 19:39:25 by fruan-ba         ###   ########.fr       */
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
	if (data->utils.can_dup)
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	if (dup2(data->utils.fd_backup, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close_descriptors(pipefd, 1, data);
	path = get_path(data, ast->cmd);
	if (handle_builtin(ast->cmd, data))
	{
		free(path);
		clean_process(data);
		exit(data->utils.exec_status);
	}
	if (data->utils.fd_backup < 0 || !data->utils.fd_backup)
        {
		if (check_list_stdin(ast->cmd))
		{
			clean_process(data);
			free(path);
			close_descriptors(pipefd, 1, data);
                	exit(0);
		}
        }
	execve(path, ast->cmd, data->utils.envp);
	clean_process(data);
	free(path);
	exit(errno);
}
