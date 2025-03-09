/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-exec_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:41:24 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/08 14:46:20 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	OBS: env[i] + 5 is for ignore "PATH=" before the paths
*/
char	*find_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*path;
	char	*temp;

	if (!cmd)
		return (NULL);
	i = 0;
	while (!ft_strnstr(env[i], "PATH", 4))
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_double_free(clear_split(paths), temp);
			return (path);
		}
		ft_double_free(path, temp);
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
