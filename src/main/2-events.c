/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-events.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:09:32 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/17 13:08:37 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_null(t_data *data)
{
	data->prompt = NULL;
	data->export_vars = NULL;
	data->token = NULL;
	data->local_vars = NULL;
}

void	create(t_data *data, char **envp)
{
	if (init_data(data, envp))
		destroy(data, NULL, 1);
	execute(data);
}

void	execute(t_data *data)
{
	display_prompt(data);
	destroy(data, NULL, 0);
}

int	destroy(t_data *data, char *message, int exit_code)
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
	if (data->export_vars)
		export_clean(&data->export_vars);
	if (data->local_vars)
		clean_locals(data->local_vars);
	set_null(data);
	if (message)
		printf("%s\n", message);
	exit (exit_code);
}
