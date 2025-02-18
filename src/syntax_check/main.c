/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:15:18 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/18 16:18:32 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_utils	data;
	t_token	*root;

	(void)argv;
	if (argc < 1)
		return (1);
	root = NULL;
	init_utils(&data);
	root = create_token("\'echo\'", CMD);
	if (!root)
		return (1);
	show_tokens(root);
	if (check_syntax(root, envp, &data))
		printf("OK\n");
	else
		printf("KO\n");
	clean_program(&data);
	return (0);
}

