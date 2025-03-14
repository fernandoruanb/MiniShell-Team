/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prompt_signal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:07:46 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/14 11:57:10 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_prompt_sig(int signal)
{
	t_data	*data;

	if (signal == SIGINT)
	{
		data = get_minishell();
		ft_putchar_fd('\n', 1);
		if (data->utils.rl_flag == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		data->utils.rl_flag = 0;
	}
}

void	handle_prompt_signal(void)
{
	signal(SIGINT, handle_prompt_sig);
	signal(SIGQUIT, SIG_IGN);
}
