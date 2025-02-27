/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:52 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/27 13:37:26 by jopereir         ###   ########.fr       */
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

static void	init_pipe(int fd[2])
{
	if (pipe(fd) < 0)
		exit (1);
}

static void	write_pipe(int fd[2])
{
	dup2(fd[1], STDOUT_FILENO);
	close_fd(fd);
}

static void	read_pipe(int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	close_fd(fd);
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

static pid_t	exec_cmd(t_ast **root, t_data *data)
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
	return (pid);
}

static pid_t	exec_cmd2(t_ast **root, t_data *data, int fd[2], int flag)
{
	pid_t	pid;
	char	*path;

	if (!*root)
		return (0);
	pid = fork();
	path = find_path((*root)->cmd[0], data->envp);
	if (!pid)
	{
		if (flag)
			write_pipe(fd);
		else
			read_pipe(fd);
		if (path)
			execve(path, (*root)->cmd, data->envp);
		perror("Erro no execve");
		exit(1);
	}
	free(path);
	return (pid);
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

static int	handle_multpipe(t_ast **root, t_data *data)
{
	pid_t	pid;

	if (!find_pipe((*root)->left, data))
		return (0);
	pid = fork();
	if (!pid)
	{
		
	}
	waitpid(pid, NULL, 0);
	return (1);
}

int	minishell(t_ast **root, t_data *data)
{
	t_ast	*ast;
	pid_t	pid;
	pid_t	pid2;
	int		fd[2];

	if (!*root)
		return (1);
	ast = *root;
	pid = 0;
	pid2 = 0;
	if (handle_builtin(ast->cmd, data))
		return (0);
	if (find_pipe(ast, data))
	{
		if (handle_multpipe(root, data))
			return (0);
		init_pipe(fd);
		pid = exec_cmd2(&ast->left, data, fd, 1);
		pid2 = exec_cmd2(&ast->right, data, fd, 0);
		close_fd(fd);
	}
	else
		pid = exec_cmd(&ast, data);
	waitpid(pid, &data->prompt->exit_status, 0);
	waitpid(pid2, &data->prompt->exit_status, 0);
	data->is_pipe = 0;
	return (0);
}
