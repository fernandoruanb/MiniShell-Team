/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directory_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:15:01 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/18 12:26:13 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_is_directory_fd(char *f, t_utils *data)
{
	if (stat(f, &data->stat_check) == -1)
		return (0);
	if (S_ISDIR(data->stat_check.st_mode))
	{
		if (f[0] == '.' || f[0] == '/')
		{
			if (access(f, F_OK) == -1)
				ft_putstr_fd(" No such file or directory\n", 2);
			else
				ft_putstr_fd(" Is a directory\n", 2);
			data->exec_status = 126;
		}
		else
		{
			if (access(f, F_OK) == -1)
				ft_putstr_fd(" No such file or directory\n", 2);
			else
				ft_putstr_fd(" command not found\n", 2);
			data->exec_status = 127;
		}
		return (1);
	}
	return (0);
}
