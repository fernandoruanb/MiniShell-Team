/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_signal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:49:44 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/12 21:42:44 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_command(int signal)
{
	t_data	*minishell;

	if (signal == SIGINT)
	{
		minishell = get_minishell();
		call_clean(minishell, minishell->flags.shoud_restore);
		clean_program(&minishell->utils);
		minishell->prompt->exit_status = 130;
		minishell->utils.exec_status = 130;
		exit(130);
	}
}

void	handle_command_signal(void)
{
	signal(SIGINT, handle_command);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}
