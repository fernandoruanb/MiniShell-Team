/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-exec_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:32:28 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/14 12:19:08 by jonas            ###   ########.fr       */
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
		printf("Syntax: KO %d\n", data->prompt->exit_status);
		return (clear_everything(data, 0));
	}
	printf("Syntax: OK\n");
	make_ast(&data->token, &data->root, data);
	printf(RED"AST\n"RESET);
	print_node(data->root);
	printf("\n");
	printf(GREEN"OUTPUT:"RESET);
	printf("\n");
	minishell(&data->root, data);
	clean_program(&data->utils);
	if (data->flags.should_clean)
		clear_everything(data, 1);
	printf("status foi atualizado de %d para ", data->prompt->exit_status);
	data->prompt->exit_status = data->utils.exec_status;
	printf("para %d\n", data->prompt->exit_status);
}
 