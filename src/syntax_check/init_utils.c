/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:28:30 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/17 18:00:47 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	helper(t_utils *data)
{
	data->index_bra_c = -1;
	data->index_bra_o = -1;
	data->brackets_o = 0;
	data->brackets_c = 0;
	data->path = NULL;
	data->simple_quotes = 0;
	data->copy_new = NULL;
	data->double_quotes = 0;
}

void	init_utils(t_utils *data, char **envp)
{
	helper(data);
	data->envp = envp;
	data->paths = NULL;
	data->line = NULL;
	data->newpwd = NULL;
	data->fd_backup = 0;
	data->oldpwd = NULL;
	data->temp = NULL;
	data->new_str = NULL;
	data->status = 0;
	data->index = 0;
	data->num_of_processes = 0;
	data->exit_status = 0;
	data->redirects = 0;
	data->pipes = 0;
	data->args = 0;
	data->commands = 0;
	data->can_dup = true;
	data->files = 0;
}
