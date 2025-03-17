/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-exec_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:32:28 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/17 18:46:25 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_everything(t_data *data, int flag)
{
	if (flag)
		clean_node(&data->root);
	token_clean(data->token);
	clear_split(data->envp);
	data->flags.should_clean = false;
}

void	analysis(t_data *data)
{
	data->envp = updateenvp(&data->export_vars);
	data->flags.should_clean = true;
	data->token = lexer(data->prompt->input, data->envp);
	if (!data->token)
	{
		if (data->flags.should_clean)
			clear_everything(data, 1);
		data->prompt->exit_status = 2;
		return ;
	}
	token_print(data->token);
	init_utils(&data->utils, data->envp);
	if (!check_syntax(data->token, data->envp, &data->utils))
	{
		data->prompt->exit_status = data->utils.exit_status;
		return (clear_everything(data, 0));
	}
	make_ast(&data->token, &data->root, data);
	minishell(&data->root, data);
	clean_program(&data->utils);
	if (data->flags.should_clean)
		clear_everything(data, 1);
	data->prompt->exit_status = data->utils.exec_status;
}
