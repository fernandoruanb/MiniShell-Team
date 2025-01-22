/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-events.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:09:32 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/21 10:43:51 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_null(t_data *data)
{
	data->temp = 0;
}

void	create(t_data *data)
{
	execute(data);
}
void	execute(t_data *data)
{
	(void)data;
	display_prompt();
}
void	destroy(t_data *data, char *message, int exit_code)
{
	set_null(data);
	if (message)
		printf("%s\n", message);
	exit (exit_code);
}
