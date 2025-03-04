/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prompt_signal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:07:46 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/26 17:24:43 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_prompt_signal(int signal)
{
	if (signal == SIGINT)
		ft_printf(BLUE"Master of universe(mini)$ "RESET);
	if (signal == SIGQUIT)
		return ;
}

void	handle_prompt_signal(int signal)
{
	signal(SIGINT, handle_prompt_sig);
	signal(SIGQUIT, handle_prompt_sig);
}
