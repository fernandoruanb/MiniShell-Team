/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:47:20 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/13 11:56:53 by jonas            ###   ########.fr       */
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

void	ft_exit(t_data *data, char *exit_status)
{
	rl_clear_history();
	data->prompt->exit_status = 0;
	if (exit_status && is_all_num(exit_status))
		data->prompt->exit_status = ft_atoi_but_better(exit_status);
	clear_split(data->utils.paths);
	printf("exit alterou o status\n");
	printf("shound clean: %s\n", data->flags.should_clean ? "OK" : "KO");
	if (data->flags.should_clean)
		call_clean(data, data->flags.shoud_restore);
	destroy(data, "Exit", data->prompt->exit_status);
}
