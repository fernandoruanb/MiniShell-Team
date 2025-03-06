/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-isbuiltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:10:30 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/06 17:40:30 by jonas            ###   ########.fr       */
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

static int	call_export(char *cmd, t_export **var)
{
	if (!cmd)
		ft_export(NULL, var);
	else
		ft_export(cmd, var);
	return (1);
}

static int	call_unset(char *cmd, t_export **export, t_localvar **locals)
{
	ft_unset(export, locals, cmd);
	return (1);
}

static int	call_local(char *cmd, t_localvar **locals)
{
	ft_localvar(cmd, locals);
	return (1);
}

int	handle_builtin(char **cmd, t_data *data)
{
	if (!ft_strcmp(cmd[0], "cd"))
		return (handle_cd(cmd, &data->export_vars));
	if (!ft_strncmp(cmd[0], "unset", 5))
		return (call_unset(cmd[1], &data->export_vars, &data->local_vars));
	if (!ft_strcmp(cmd[0], "export"))
		return (call_export(cmd[1], &data->export_vars));
	else if (ft_strnstr(cmd[0], "=", ft_strlen(cmd[0])))
		return (call_local(cmd[0], &data->local_vars));
	return (0);
}
