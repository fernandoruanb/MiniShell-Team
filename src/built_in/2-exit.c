/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:47:20 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/28 15:51:09 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_all_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int	ft_exit(char *name, t_prompt *prompt, char *exit_status)
{
	printf("exit\n");
	rl_clear_history();
	ft_free(name, NULL);
	if (exit_status)
	{
		if (!is_all_num(exit_status))
		prompt->exit_status = ft_atoi(exit_status);
	}
	else
		prompt->exit_status = 0;
	
	return (prompt->exit_status);
}
