/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:05:17 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/21 18:58:41 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_read_mode(t_ast **root, int *pipefd, t_data *data)
{
	char	*path;
	t_ast	*ast;

	ast = *root;
	handle_command_signal();
	path = NULL;
	if (data->utils.can_read)
		if (dup2(data->utils.fd_backup, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	close_descriptors(pipefd, 1, data);
	path = get_path(data, ast->cmd);
	// if (handle_builtin(ast->cmd, data))
	// {
	// 	ultimate_check(ast, path, pipefd, data);
	// 	clean_process(data);
	// 	exit(data->utils.exec_status);
	// }
	ultimate_check(ast, path, pipefd, data);
	if (!handle_builtin(ast->cmd, data))
		if (execve(path, ast->cmd, data->utils.envp) < 0)
			data->utils.exec_status = errno;
	free(path);
	clean_process(data);
	close_all_fds();
	exit(data->utils.exec_status);
}
