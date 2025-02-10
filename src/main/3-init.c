/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:09:27 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/10 13:40:30 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_data(t_data *data, char **envp)
{
	data->prompt = ft_calloc(1, sizeof(t_prompt));
	if (!data->prompt)
		return (1);
	init_utils(&data->utils);
	data->prompt->envp = envp;
	data->prompt->pid = -1;
	data->prompt->input = NULL;
	data->prompt->cmdset = NULL;
	data->prompt->path = NULL;
	data->prompt->exit_status = 0;
	data->token = NULL;
	return (0);
}
