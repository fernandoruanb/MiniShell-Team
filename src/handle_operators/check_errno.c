/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errno.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:51:37 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/08 22:28:05 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_errno(char **split1, t_utils *data)
{
	char	*path;

	if (access(split1[0], F_OK | X_OK))
		path = find_path(split1[0], data->envp);
	else
		path = split1[0];
	if (path == NULL)
	{
		free_splits(NULL, split1, NULL, NULL);
		data->exec_status = 127;
		exit(127);
	}
	if (execve(path, split1, data->envp) == -1)
	{
		free_splits(NULL, split1, NULL, NULL);
		free(path);
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES)
			exit(126);
		else
			exit(errno);
	}
}
