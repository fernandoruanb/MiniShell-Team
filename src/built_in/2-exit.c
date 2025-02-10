/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:47:20 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/10 10:21:55 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_all_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

void	ft_exit(char *name, t_data *data, char *exit_status)
{
	rl_clear_history();
	free(name);
	data->prompt->exit_status = 0;
	if (exit_status && is_all_num(exit_status))
		destroy(data, "Exit", ft_atoi(exit_status));
	destroy(data, "Exit", data->prompt->exit_status);
}
