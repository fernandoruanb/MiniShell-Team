/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-isbuiltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:10:30 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/24 16:03:41 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_cd(char **cmd, t_export **export)
{
	// if (!ft_strcmp(cmd[1], "-"))
	// {
	// 	free(cmd[1]);
	// 	cmd[1] = NULL;
	// 	cmd[1] = ft_strdup(search_var(export, "OLDPWD")->value);
	// }
	(void)export;
	ft_cd(cmd[1]);
	return (1);
}

int	handle_builtin(char **cmd, t_data *data)
{
	if (!ft_strcmp(cmd[0], "cd"))
		return (handle_cd(cmd, &data->export_vars));
	if (!ft_strcmp(cmd[0], "export"))
	{
		if (cmd[1])
			ft_export(cmd[1], &data->export_vars);
		else
			ft_export(NULL, &data->export_vars);
		return (1);
	}
	else if (ft_strnstr(cmd[0], "=", ft_strlen(cmd[0])))
	{
		ft_localvar(cmd[0], &data->local_vars);
		return (1);
	}
	if (!ft_strncmp(cmd[0], "unset", 5))
	{
		ft_unset(&data->export_vars, &data->local_vars, cmd[1]);
		return (1);
	}
	return (0);
}
