/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-exec_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:41:24 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/10 13:54:30 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*helper(char *path, char *cmd)
{
	char	*temp;
	char	*new;

	temp = ft_strjoin(path, "/");
	new = ft_strjoin(temp, cmd);
	free(temp);
	return (new);
}

/*
	OBS: env[i] + 5 is for ignore "PATH=" before the paths
*/
char	*find_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*path;

	if (!cmd)
		return (NULL);
	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH", 4))
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = helper(paths[i], cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			clear_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	return (clear_split(paths));
}

// pid_t	exec_cmd(t_ast **root, t_data *data)
// {
// 	pid_t	pid;
// 	char	*path;

// 	pid = fork();
// 	if (!pid)
// 	{
// 		if (access((*root)->cmd[0], F_OK | X_OK))
// 			path = find_path((*root)->cmd[0], data->envp);
// 		else
// 			path = (*root)->cmd[0];
// 		if (path)
// 			execve(path, (*root)->cmd, data->envp);
// 		perror("Erro no execve");
// 		free(path);
// 		exit(1);
// 	}
// 	return (pid);
// }
