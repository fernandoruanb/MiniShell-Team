/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-exec_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:21:40 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/28 11:34:37 by jopereir         ###   ########.fr       */
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

int	child(t_prompt *prompt)
{
	prompt->path = find_path(prompt->cmdset[0], prompt->envp);
	if (!prompt->path)
		return (1);
	prompt->pid = fork();
	if (prompt->pid < 0)
		return (1);
	if (prompt->pid == 0)
		execute_proccess(prompt);
	waitpid(prompt->pid, &prompt->exit_status, 0);
	return (0);
}

// static int	luke_i_am_your_father(t_prompt *prompt)
// {
// 	char	**pipes;
// 	int		i;

// 	pipes = ft_split(prompt->input, '|');
// 	if (!pipes)
// 		return (1);
// 	free(prompt->input);
// 	i = 0;
// 	while (pipes[i])
// 	{
// 		prompt->input = ft_strdup(pipes[i]);
// 		free(prompt->input);
// 		if (child(prompt))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

void	exec_cmd(t_prompt *prompt)
{
	// if (ft_strchr(prompt->input, '|'))
	// 	if (luke_i_am_your_father(prompt))
	// 		return ;

	if (ft_strncmp(prompt->input, "cd", 2) == 0)
		ft_cd(prompt->input);
	prompt->cmdset = ft_split(prompt->input, ' ');
	if (ft_strncmp(prompt->cmdset[0], "echo", 5) == 0)
		return (ft_echo(prompt));
	if (prompt->input != NULL)
		child(prompt);
}
