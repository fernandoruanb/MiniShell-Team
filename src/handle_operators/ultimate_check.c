/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:48:13 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/20 10:48:13 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ultimate_check(t_ast *ast, char *path, int *pipefd, t_data *data)
{
	if (data->utils.fd_backup < 0 || !data->utils.fd_backup)
	{
		if (check_list_stdin(ast->cmd) && data->utils.can_read)
		{
			clean_process(data);
			free(path);
			close_descriptors(pipefd, 1, data);
			exit (0);
		}
	}
}
