/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:36:24 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/28 15:41:22 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	single_command(char *cmd, t_utils *data)
{
	char	**split1;
	int	pid;

	split1 = ft_split(cmd, ' ');
	if (!split1)
		return ;
	pid = fork();
	if (pid == -1)
	{
		free_splits(NULL, split1, NULL, NULL);
		return ;
	}
	if (pid == 0)
		check_errno(split1, data);
	free_splits(NULL, split1, NULL, NULL);
	waitpid(pid, &data->exec_status, 0);
}
