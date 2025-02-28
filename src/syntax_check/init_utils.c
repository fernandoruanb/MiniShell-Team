/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:28:30 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/28 10:15:02 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_utils(t_utils *data)
{
	data->index_bra_c = -1;
	data->index_bra_o = -1;
	data->brackets_o = 0;
	data->brackets_c = 0;
	data->path = NULL;
	data->simple_quotes = 0;
	data->copy_new = NULL;
	data->double_quotes = 0;
	data->paths = NULL;
	data->temp = NULL;
	data->new_str = NULL;
	data->status = 0;
	data->old = NULL;
	data->cmd = NULL;
	data->exit_status = 0;
	data->redirects = 0;
	data->pipes = 0;
	data->args = 0;
	data->commands = 0;
	data->files = 0;
}
