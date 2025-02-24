/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:11:23 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/24 10:12:09 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_brackets_start(t_token *root)
{
	t_token	*last;
	int		flag;

	last = root;
	flag = 0;
	while (last)
	{
		if (last->id == BRACKET_O)
			flag = 1;
		else if (last->id == BRACKET_C)
			flag = 0;
		last = last->next;
	}
	if (flag == 1)
		return (0);
	return (1);
}

int	check_syntax(t_token *root, char **envp, t_utils *data)
{
	int		flag;
	t_token	*go;

	if (!check_brackets_start(root))
		return (show_error_fd("Syntax Error: BRACKETS", 0, data, 2));
	get_paths(envp, data);
	if (!data->paths)
		return (0);
	flag = 1;
	go = root;
	while (flag && go)
	{
		flag = get_command(go, data);
		go = go->next;
	}
	if (flag != 1)
		return (0);
	if (data->brackets_o != data->brackets_c)
		return (show_error_fd("Syntax: BRACKET Error", 0, data, 2));
	return (1);
}
