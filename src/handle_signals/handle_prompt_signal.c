/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prompt_signal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:07:46 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/12 16:50:23 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_prompt_sig(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
}

void	handle_prompt_signal(void)
{
	signal(SIGINT, handle_prompt_sig);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}
