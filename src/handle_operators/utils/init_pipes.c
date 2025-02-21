/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:33:31 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/21 18:03:23 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	close_descriptors(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}

static void	clean_all_pipes(t_utils *data)
{
	int	index;

	index = 0;
	while (index < data->pipes)
	{
		free(data->pipes_fd[index]);
		index++;
	}
}

int	init_pipes(t_token *root, t_utils *data)
{
	int	pipes;
	int	index;

	data->pipes = get_pipes(root);
	data->pipes_fd = malloc(data->pipes * sizeof(int [2]));
	if (!data->pipes_fd)
		return (0);
	index = 0;
	while (index < pipes)
	{
		if (pipe(data->pipes_fd[index]) == -1)
		{
			clean_all_pipes(data);
			return (0);
		}
		index++;
	}
	return (1);
}
