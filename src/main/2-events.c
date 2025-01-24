/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-events.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:09:32 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/24 13:22:38 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_null(t_data *data)
{
	data->prompt = NULL;
}

void	create(t_data *data, char **envp)
{
	if (init_data(data, envp))
		destroy(data, NULL, 1);
	execute(data);
}
void	execute(t_data *data)
{
	display_prompt(data->prompt);
	destroy(data, "Successfully destroyes", 0);
}
void	destroy(t_data *data, char *message, int exit_code)
{
	if (data->prompt)
	{
		if (data->prompt->path)
			free(data->prompt->path);
		if (data->prompt->input)
			free(data->prompt->input);
		if (data->prompt->cmdset)
			clear_split(data->prompt->cmdset);
		free(data->prompt);
	}
	set_null(data);
	if (message)
		printf("%s\n", message);
	exit (exit_code);
}
