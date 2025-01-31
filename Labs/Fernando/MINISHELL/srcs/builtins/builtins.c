/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:03:49 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/29 14:39:23 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtins(t_data *data)
{
	if (ft_strncmp(data->line, "cd", 2) == 0)
	{
		ft_cd(data);
		return (1);
	}
	else if (ft_strncmp(data->line, "clear", 5) == 0)
	{
		write(1, "\033[H\033[J", 7);
		return (1);
	}
	else if (ft_strncmp(data->line, "env", 3) == 0)
	{
		ft_env(data);
		return (1);
	}
	else if (ft_strncmp(data->line, "echo", 4) == 0)
	{
		ft_echo(data);
		return (1);
	}
	return (0);
}
