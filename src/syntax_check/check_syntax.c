/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:11:23 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 12:11:41 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_syntax(t_token *root, char **envp, t_utils *data)
{
	int	flag;

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
	return (1);
}
