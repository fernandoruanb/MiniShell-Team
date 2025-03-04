/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-events.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:31:43 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/04 15:31:47 by fruan-ba         ###   ########.fr       */
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
		// if (data->prompt->cmdset)
		// 	while (data->prompt->cmdset[i])
		// 		clear_split(data->prompt->cmdset[i++]);
		// 	(void)clean_array(data->prompt->cmdset);
		free(data->prompt);
	}
	if (data->root)
		clean_node(&data->root);
	if (data->export_vars)
		export_clean(&data->export_vars);
	if (data->local_vars)
		clean_locals(data->local_vars);
	set_null(data);
	if (message)
		printf("%s\n", message);
	exit (exit_code);
}
