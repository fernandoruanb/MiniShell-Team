/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:00:38 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/29 10:19:51 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	execute_command(char *cmd, char **envp)
{
	char	*paths_temp;
	char	**paths;
	char	*path;
	int		index;
	char	**commands;

	index = 0;
	while (!ft_strnstr(envp[index], "PATH", 4))
		index++;
	paths_temp = ft_strdup(envp[index] + 5);
	if (!paths_temp)
		return (1);
	paths = ft_split(paths_temp, ':');
	if (!paths)
		return (free_splits(paths_temp, NULL, NULL, NULL));
	commands = ft_split(cmd, ' ');
	if (!commands)
		return (free_splits(paths_temp, paths, NULL, NULL));
	path = find_path(commands[0], paths);
	if (!path)
		return (free_splits(paths_temp, paths, commands, NULL));
	if (execve(path, commands, envp) == -1)
		exit(EXIT_FAILURE);
	return (1);
}
