/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errno.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:51:37 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/11 17:59:57 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_errno(char **split1, t_utils *data, t_data *__data)
{
	char	*path;

	if (access(split1[0], F_OK | X_OK))
	{
		path = find_path(split1[0], data->envp, __data);
		if (!path)
		{
			if (__data->prompt)
			{
				if (__data->prompt->input)
					free(__data->prompt->input);
				free(__data->prompt);
			}
			data->exec_status = 127;
			exit(127);
		}
	}
	else
		path = ft_strdup(split1[0]);
	execve(path, split1, data->envp);
	call_clean(__data);
	free(path);
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES)
		exit(126);
	else
		exit(errno);
}
