/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-exec_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:21:40 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/24 14:21:53 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	OBS: env[i] + 5 is for ignore "PATH=" before the paths
*/
static	char	*find_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	while (!ft_strnstr(env[i], "PATH", 4))
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			clear_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	clear_split(paths);
	return (NULL);
}

static void	execute_proccess(t_prompt *prompt)
{
	if (execve(prompt->path, prompt->cmdset, prompt->envp) == -1)
		exit(1);
}

static int	child(t_prompt *prompt)
{
	prompt->cmdset = ft_split(prompt->input, ' ');
	prompt->path = find_path(prompt->cmdset[0], prompt->envp);
	if (!prompt->path)
		return (1);
	prompt->pid = fork();
	if (prompt->pid < 0)
		return (1);
	if (prompt->pid == 0)
		execute_proccess(prompt);
	waitpid(prompt->pid, NULL, 0);
	return (0);
}

void	exec_cmd(t_prompt *prompt)
{
	if (child(prompt))
		return ;
}
