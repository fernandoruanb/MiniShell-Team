/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-exec_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:32:28 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/13 22:00:41 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Excluir isso antes de entregar
*/
void	ast_print(t_ast *root, int level)
{
	if (!root)
		return ;
	ast_print(root->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("     ");
	printf("%s (%d)(%s)\n", root->cmd[0], root->index, root->id == CMD ? "CMD" : root->id == LIMITER ? "LIMITER" : root->id == FD ? "FD" : root->id == PIPE ? "PIPE" : "REDIRECT");
	ast_print(root->left, level + 1);
}

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
	data->token = lexer(data->prompt->input, data->envp);
	if (!data->token)
	{
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
	data->flags.should_clean = true;
	printf(RED"AST\n"RESET);
	ast_print(data->root, 0);
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
 