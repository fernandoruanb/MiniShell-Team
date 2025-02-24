/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:52 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/24 15:39:47 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	find_cmd(t_data *data, char ***cmd, int *i)
// {
// 	if (cmd[*i] == 0)
// 		return ;
// 	if (!ft_strcmp(cmd[*i][0], "|"))
// 	{
// 		data->isPipe = 1;
// 		(*i)++;
// 	}
// }

// static void	init_pipe(t_data *data)
// {
// 	if (!data->isPipe)
// 		return ;
// 	if (pipe(data->fd) < 0)
// 		exit (1);
// }

// /*
// 	OBS: env[i] + 5 is for ignore "PATH=" before the paths
// */
// static	char	*find_path(char *cmd, char **env)
// {
// 	int		i;
// 	char	**paths;
// 	char	*path;
// 	char	*temp;

// 	if (!cmd)
// 		return (NULL);
// 	i = 0;
// 	while (!ft_strnstr(env[i], "PATH", 4))
// 		i++;
// 	paths = ft_split(env[i] + 5, ':');
// 	i = 0;
// 	while (paths[i])
// 	{
// 		temp = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(temp, cmd);
// 		if (access(path, F_OK | X_OK) == 0)
// 		{
// 			ft_double_free(clear_split(paths), temp);
// 			return (path);
// 		}
// 		ft_double_free(path, temp);
// 		i++;
// 	}
// 	return (clear_split(paths));
// }

// static void	exec_cmd(char ***cmd, int i, char **envp, t_data *data)
// {
// 	pid_t	pid;
// 	char	*path;

// 	pid = fork();
// 	path = find_path(cmd[i][0], envp);
// 	if (!pid)
// 	{
// 		if (data->isPipe)
// 		{
// 			dup2(data->fd[1], 1);
// 			close(data->fd[1]);
// 			close(data->fd[0]);
// 		}
// 		execve(path, cmd[i], envp);
// 		exit(1);
// 	}
// 	else if (data->isPipe)
// 	{
// 		dup2(data->fd[0], 0);
// 		close(data->fd[0]);
// 		close(data->fd[1]);
// 	}
// 	waitpid(pid, &data->prompt->exit_status, 0);
// }

// int	minishell(t_data *data)
// {
// 	int		i;
// 	char	***cmd;

// 	cmd = data->prompt->cmdset;
// 	i = 0;
// 	if (handle_builtin(cmd, data))
// 		return (0);
// 	while (cmd[i])
// 	{
// 		data->isPipe = 0;
// 		find_cmd(data, cmd, &i);
// 		init_pipe(data);
// 		printf("Output:\n");
// 		exec_cmd(cmd, i, data->prompt->envp, data);
// 		clear_split(cmd[i++]);
// 	}
// 	return (0);
// }

int	minishell(t_ast **root, t_data *data)
{
	t_ast	*ast;

	ast = *root;
	if (handle_builtin(ast->cmd, data))
		return (0);
	return (0);
}
