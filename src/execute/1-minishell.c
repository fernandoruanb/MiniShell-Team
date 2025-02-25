/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:52 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/25 15:20:59 by jopereir         ###   ########.fr       */
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

static void	close_fd(int fd[2])
{
	close(fd[1]);
	close(fd[0]);
}

static void	init_pipe(t_data *data)
{
	if (pipe(data->fd) < 0)
		exit (1);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
}

static void	read_pipe(t_data *data)
{
	dup2(data->fd[0], STDIN_FILENO);
	close (data->fd[1]);
}


/*
	OBS: env[i] + 5 is for ignore "PATH=" before the paths
*/
static	char	*find_path(char *cmd, char **env)
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

static void	exec_cmd(t_ast **root, t_data *data)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	path = find_path((*root)->cmd[0], data->envp);
	if (!pid)
	{
		execve(path, (*root)->cmd, data->envp);
		perror("Erro no execve");
		exit(1);
	}
	free(path);
	waitpid(pid, &data->prompt->exit_status, 0);
	if (data->is_pipe)
		close_fd(data->fd);
}

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

static int	find_pipe(t_ast *root, t_data *data)
{
	if (!root || !root->cmd)
		return (0);
	if (!ft_strcmp(root->cmd[0], "|"))
		data->is_pipe = 1;
	return (data->is_pipe);
}

int	minishell(t_ast **root, t_data *data)
{
	t_ast	*ast;

	if (!*root)
		return (0);
	ast = *root;

	if (handle_builtin(ast->cmd, data))
		return (0);
	if (find_pipe(ast, data))
	{
		init_pipe(data);
		exec_cmd(&ast->left, data);
		read_pipe(data);
		exec_cmd(&ast->right, data);
		close_fd(data->fd);
	}
	else
		exec_cmd(&ast, data);
	return (0);
}
