/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:11:23 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/15 20:09:28 by fruan-ba         ###   ########.fr       */
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
	int	flag;

	if (!check_brackets_start(root))
		return (show_error_fd("Syntax Error: BRACKETS", 0, data, 0));
	get_paths(envp, data);
	if (!data->paths)
		return (0);
	flag = 1;
	while (root)
	{
		if (get_command(root, data))
			root = root->next;
		else
		{
			flag = 0;
			break ;
		}
	}
	if (flag != 1)
		return (0);
	if (data->brackets_o != data->brackets_c)
		return (show_error_fd("Syntax: BRACKET Error", 0, data, 0));
	return (1);
}
