/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_list_stdin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:22:45 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/17 19:22:50 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_list_stdin(char **cmd)
{
	int	index;
	static char *stdin_cmds[] = {"cat","sort", NULL};

	index = 0;
	while (stdin_cmds[index] != NULL)
	{
		if (ft_strcmp(cmd[0], stdin_cmds[index]) == 0)
			return (1);
		index++;
	}
	return (0);
}
