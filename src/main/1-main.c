/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:09:08 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/28 10:45:01 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signal)
{
	if (signal == SIGINT)
		printf("\n<<Master of universe(mini)>>");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	signal(SIGINT, handle_signal);
	if (argc != 1)
		return (1);
	create(&data, envp);
	return (0);
}
