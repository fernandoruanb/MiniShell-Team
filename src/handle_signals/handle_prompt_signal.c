/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prompt_signal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:07:46 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/05 11:34:18 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_prompt_sig(int signal)
{
	if (signal == SIGINT)
		ft_printf(BLUE"Master of universe(mini)$ "RESET);
}

void	handle_prompt_signal(void)
{
	signal(SIGINT, handle_prompt_sig);
	signal(SIGQUIT, SIG_IGN);
}
