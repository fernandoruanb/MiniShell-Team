/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-isbuiltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:10:30 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/24 07:38:35 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtin(char ***cmd, t_data *data)
{
	if (!ft_strcmp(cmd[0][0], "cd"))
	{
		ft_cd(cmd[0][1]);
		return (1);
	}
	if (!ft_strcmp(cmd[0][0], "export"))
	{
		if (cmd[0][1])
			ft_export(cmd[0][1], &data->export_vars);
		else
			ft_export(NULL, &data->export_vars);
		return (1);
	}
	else if (ft_strnstr(cmd[0][0], "=", ft_strlen(cmd[0][0])))
	{
		ft_localvar(cmd[0][0], &data->local_vars);
		return (1);
	}
	if (!ft_strncmp(cmd[0][0], "unset", 5))
	{
		ft_unset(&data->export_vars, &data->local_vars, cmd[0][1]);
		return (1);
	}
	return (0);
}
