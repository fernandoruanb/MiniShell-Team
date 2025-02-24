/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:33:31 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/24 12:18:16 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	clean_all_pipes(t_utils *data, int index)
{
	int	stop;

	if (index < 0)
		return ;
	stop = 0;
	while (stop < index)
	{
		close(data->pipes_fd[index][0]);
		close(data->pipes_fd[index][1]);
		stop++;
	}
}

int	init_pipes(t_utils *data)
{
	int	index;

	data->pipes_fd = (int **)malloc(data->pipes * sizeof(int *));
	if (!data->pipes_fd)
		return (0);
	index = 0;
	while (index < data->pipes)
	{
		if (pipe(data->pipes_fd[index]) == -1)
		{
			clean_all_pipes(data, --index);
			return (0);
		}
		index++;
	}
	return (1);
}
