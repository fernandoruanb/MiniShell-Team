// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   1-minishell.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/21 10:24:52 by jopereir          #+#    #+#             */
// /*   Updated: 2025/03/04 10:16:53 by jopereir         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "minishell.h"

// // static void	find_cmd(t_data *data, char ***cmd, int *i)
// // {
// // 	if (cmd[*i] == 0)
// // 		return ;
// // 	if (!ft_strcmp(cmd[*i][0], "|"))
// // 	{
// // 		data->isPipe = 1;
// // 		(*i)++;
// // 	}
// // }

// // static void	close_fd(int fd[2])
// // {
// // 	close(fd[1]);
// // 	close(fd[0]);
// // }

// static void	init_pipe(int fd[2])
// {
// 	if (pipe(fd) < 0)
// 		exit (1);
// }

// // static void	write_pipe(int fd[2])
// // {
// // 	close(fd[0]);
// // 	if (dup2(fd[1], 1) < 0)
// // 		exit(1);
// // }

// // static void	read_pipe(int fd[2])
// // {
// // 	close(fd[1]);
// // 	if (dup2(fd[0], 0) < 0)
// // 		exit (1);
// // }

// // static void	read_write_pipe(int fd[2])
// // {
// // 	if (dup2(fd[0], 0) < 0
// // 		|| dup2(fd[1], 1) < 0)
// // 		exit (1);
// // }

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

// static pid_t	exec_cmd(t_ast **root, t_data *data)
// {
// 	pid_t	pid;
// 	char	*path;

// 	pid = fork();
// 	if (!pid)
// 	{
// 		path = find_path((*root)->cmd[0], data->envp);
// 		execve(path, (*root)->cmd, data->envp);
// 		perror("Erro no execve");
// 		free(path);
// 		exit(1);
// 	}
// 	return (pid);
// }

// static pid_t	exec_cmd2(t_ast **root, t_data *data, int fd[2], int flag)
// {
// 	pid_t	pid;
// 	char	*path;

// 	if (!*root)
// 		return (0);
// 	pid = fork();
// 	path = find_path((*root)->cmd[0], data->envp);
// 	if (!pid)
// 	{
// 		if (flag == 1)
// 			write_pipe(fd);
// 		else if (flag == 3)
// 			read_pipe(fd);
// 		else if (flag == 2)
// 			read_write_pipe(fd);
// 		if (path)
// 			execve(path, (*root)->cmd, data->envp);
// 		perror("Erro no execve");
// 		exit(1);
// 	}
// 	free(path);
// 	return (pid);
// }

// // int	minishell(t_data *data)
// // {
// // 	int		i;
// // 	char	***cmd;

// // 	cmd = data->prompt->cmdset;
// // 	i = 0;
// // 	if (handle_builtin(cmd, data))
// // 		return (0);
// // 	while (cmd[i])
// // 	{
// // 		data->isPipe = 0;
// // 		find_cmd(data, cmd, &i);
// // 		init_pipe(data);
// // 		printf("Output:\n");
// // 		exec_cmd(cmd, i, data->prompt->envp, data);
// // 		clear_split(cmd[i++]);
// // 	}
// // 	return (0);
// // }

// static int	find_pipe(t_ast *root, t_data *data)
// {
// 	if (!root || !root->cmd)
// 		return (0);
// 	if (!ft_strcmp(root->cmd[0], "|"))
// 		data->is_pipe = 1;
// 	return (data->is_pipe);
// }
// // 
// // static int	handle_multpipe(t_ast **root, t_data *data)
// // {
// // 	pid_t	pid;

// // 	if (!find_pipe((*root)->left, data))
// // 		return (0);
// // 	pid = fork();
// // 	if (!pid)
// // 	{
		
// // 	}
// // 	waitpid(pid, NULL, 0);
// // 	return (1);
// // }

// // static int	count_pipes(t_ast **root)
// // {
// // 	int	cnt;

// // 	if (!*root)
// // 		return (0);
// // 	cnt = count_pipes(&(*root)->left);
// // 	if (!ft_strcmp((*root)->cmd[0], "|"))
// // 		cnt++;
// // 	cnt += count_pipes(&(*root)->right); 
// // 	return (cnt);
// // }

// static int	high_index(t_ast **root)
// {
// 	int	left;
// 	int	right;

// 	if (!*root)
// 		return (0);
// 	left = high_index(&(*root)->left);
// 	right = high_index(&(*root)->right);
// 	if (left == right)
// 		return ((*root)->index);
// 	if (left > right)
// 		return (left);
// 	return (right);
// }

// // int	minishell(t_ast **root, t_data *data, int fd[2])
// // {
// // 	t_ast	*ast;
// // 	pid_t	pid;
// // 	pid_t	pid2;
// // 	int		flg;

// // 	if (!*root)
// // 		return (1);
// // 	// if (find_pipe((*root)->left, data))
// // 	// 	minishell(&(*root)->left, data);
// // 	ast = *root;
// // 	pid = 0;
// // 	flg = 0;
// // 	pid2 = 0;
// // 	if (handle_builtin(ast->cmd, data))
// // 		return (0);
// // 	if (find_pipe(ast, data))
// // 	{
// // 		init_pipe(fd);
// // 		// minishell(&(*root)->left, data, fid);
// // 		// minishell(&(*root)->right, data, fid);
// // 		if (ast->left->index == 0)
// // 			flg = 1;
// // 		else
// // 			flg = 2 + high_index(root) == ast->index;
// // 		pid = exec_cmd2(&ast->left, data, fd, flg);
// // 		//printf("pipes: %d\n", count_pipes(&ast));
// // 		flg = 2 + high_index(root) == ast->index;
// // 		if (ast->right)
// // 			pid2 = exec_cmd2(&ast->right, data, fd, flg);
// // 		close_fd(fd);
// // 	}
// // 	else
// // 		pid = exec_cmd(&ast, data);
// // 	waitpid(pid, &data->prompt->exit_status, 0);
// // 	waitpid(pid2, &data->prompt->exit_status, 0);
// // 	data->is_pipe = 0;
// // 	return (0);
// // }

// int	init_flg(t_ast **root)
// {
// 	int	flag;

// 	if (!*root)
// 		return (0);
// 	if ((*root)->index == 0)
// 		return (1);
// 	flag = 2 + (high_index(root) == (*root)->index);
// 	return (flag);
// }

// // int	init_all_pipes(t_ast **root)
// // {
// // 	t_ast	*ast;

// // 	if (!*root)
// // 		return (0);
// // 	ast = *root;
// // 	while (ast->left)
// // 	{
		
// // 	}
// // }

// // static int	cntcmd(t_token **token)
// // {
// // 	int		cnt;
// // 	t_token	*temp;

// // 	temp = *token;
// // 	cnt = 0;
// // 	while (temp)
// // 	{
// // 		cnt += temp->id == CMD;
// // 		temp = temp->next;
// // 	}
// // 	return (cnt);
// // }
// ast = *root;
// 		return ;
// 	if (find_pipe((*root)->left, data))
// 	{
// 		init_pipe(fd);
// 		handle_pipes(&(*root)->left, data);
// 	}
// }

int	minishell(t_ast **root, t_data *data)
{
	// t_ast	*ast;
	// pid_t	pid;
	
	if (!*root)
		return (1);
	// ast = *root;
	if (handle_builtin((*root)->cmd, data)) // Ver quando tiver pipe
		return (0);
	// if (find_pipe(ast, data))
	// 	handle_pipes(root, data);
	// else
	// {
	//	pid = exec_cmd(&ast, data);
	//	waitpid(pid, &data->prompt->exit_status, 0);
	//}


	// if (ast->type == CMD)
	// {
	// 	pid = exec_cmd(&ast, data);
	// 	waitpid(pid, &data->prompt->exit_status, 0);
	// 	// extrair return code
	// }
	
	return (0);
}
