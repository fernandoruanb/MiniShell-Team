/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:26:26 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/29 13:13:24 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	find_pipes(t_data *data)
{
	int	index;

	index = 0;
	while (data->line[index] != '\0')
	{
		if (data->line[index] == '|')
			data->pipes++;
		index++;
	}
}

static void	central_control(char **s_l, t_data *data, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (data->pipes == 0)
		{
			free_splits(NULL, s_l, NULL, NULL);
			execute_command(data->line, envp);
			exit(EXIT_SUCCESS);
		}
	}
	waitpid(pid, &data->status, 0);
}

void	execute(t_data *data, char **envp)
{
	char	**split_line;

	split_line = ft_split(data->line, ' ');
	if (!split_line)
		return ;
	find_pipes(data);
	central_control(split_line, data, envp);
}
