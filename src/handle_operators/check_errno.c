/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errno.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:51:37 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/26 18:55:54 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_errno(char **split1, t_utils *data)
{
	if (execve(split1[0], split1, data->envp) == -1)
	{
		free_splits(NULL, split1, NULL, NULL);
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES)
			exit(126);
		else
			exit(errno);
	}
}
