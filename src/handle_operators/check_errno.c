/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errno.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:51:37 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/14 10:56:26 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_process(t_data *data)
{
	if (!data)
		return ;
	if (data->prompt)
	{
		if (data->prompt->input)
			free(data->prompt->input);
		free(data->prompt);
		data->prompt = NULL;
	}
	call_clean(data, data->flags.shoud_restore);
	clean_program(&data->utils);
}

void	check_errno(char **split1, t_utils *data, t_data *__data)
{
	char	*path;

	handle_command_signal();
	if (ft_strcmp(split1[0], "sudo") == 0)
	{
		data->exec_status = 126;
		clean_process(__data);
		ft_printf("sudo: permission denied\n");
		exit(126);
	}
	path = get_path(__data, split1);
	printf("vou executar %s\n", path);
	execve(path, split1, data->envp);
	clean_process(__data);
	free(path);
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES)
		exit(126);
	else
		exit(errno);
}
