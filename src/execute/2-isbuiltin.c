/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-isbuiltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:10:30 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/14 16:39:49 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_cd(char **cmd)
{
	ft_cd(cmd[1]);
	return (1);
}

static int	call_export(char **cmd, t_export **var, t_data *data)
{
	data->utils.exec_status = ft_export(cmd, var);
	return (1);
}

static int	call_unset(char *cmd, t_export **export, t_localvar **locals)
{
	ft_unset(export, locals, cmd);
	return (1);
}

static int	call_local(char *cmd, t_localvar **locals, t_data *data)
{
	data->utils.exec_status = ft_localvar(cmd, locals);
	return (1);
}

int	handle_builtin(char **cmd, t_data *data)
{
	if (!ft_strcmp(cmd[0], "cd"))
		return (handle_cd(cmd));
	if (!ft_strcmp(cmd[0], "clear"))
	{
		write(1, "\033[H\033[J", 7);
		return (1);
	}
	if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd(data));
	if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(data));
	if (!ft_strcmp(cmd[0], "echo"))
		return (call_echo(data, &cmd[1]));
	if (!ft_strncmp(cmd[0], "unset", 5))
		return (call_unset(cmd[1], &data->export_vars, &data->local_vars));
	if (!ft_strcmp(cmd[0], "export"))
		return (call_export(&cmd[1], &data->export_vars, data));
	else if (ft_strnstr(cmd[0], "=", ft_strlen(cmd[0])))
		return (call_local(cmd[0], &data->local_vars, data));
	if (!ft_strcmp(cmd[0], "exit"))
	{
		ft_exit(data, cmd[1]);
		return (1);
	}
	return (0);
}
