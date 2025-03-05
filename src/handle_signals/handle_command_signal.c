/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_signal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:49:44 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/05 12:24:47 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_command(int signal)
{
	if (signal == SIGINT)
		exit(130);
}

void	handle_command_signal(void)
{
	signal(SIGINT, handle_command);
	signal(SIGQUIT, SIG_IGN);
}
