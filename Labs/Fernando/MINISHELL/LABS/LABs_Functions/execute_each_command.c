/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_each_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:08:54 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/26 10:31:21 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	last_command(int pipefds[][2], char **argv, char **envp)
{
	int		argc;
	int		output;
	char	**split_paths;
	char	*path;

	argc = count_args(argv);
	close(pipefds[argc - 1][1]);
	output = open(argv[argc], O_WRONLY, O_CREAT, O_TRUNC, 0644);
	if (output == -1)
		exit((clean_all_pipes_also_fd(argc, pipefds, 0)) * -1);
	if (dup2(output, STDOUT_FILENO) == -1)
		exit((clean_all_pipes_also_fd(argc, pipefds, output)) * -1);
	if (dup2(pipefds[argc - 1][0], STDIN_FILENO) == -1)
		exit((clean_all_pipes_also_fd(argc, pipefds, output)) * -1);
	close(output);
	close(pipefds[argc - 1][0]);
	split_paths = split_path(argc, argv, envp);
	if (!split_paths)
		exit((clean_all_pipes_also_fd(argc, pipefds, output)) * -1);
	path = find_path(argv[argc], split_paths);
	if (!path)
		exit((clean_all_pipes_also_fd(argc, pipefds, output)) * -1);
	execve(path, ft_split(argv[argc], ' '), NULL);
}

static void	middle_command(int i, int pipefds[][2], char **argv, char **envp)
{
	int		argc;
	char	**split_paths;
	char	*path;

	close(pipefds[i - 1][1]);
	close(pipefds[i + 1][0]);
	argc = count_args(argv);
	if (dup2(pipefds[i - 1][0], STDIN_FILENO) == -1)
		exit((clean_all_pipes_also_fd(argc, pipefds, 0)) * -1);
	if (dup2(pipefds[i + 1][1], STDOUT_FILENO) == -1)
		exit((clean_all_pipes_also_fd(argc, pipefds, 0)) * -1);
	close(pipefds[i - 1][0]);
	close(pipefds[i + 1][1]);
	split_paths = split_path(argc, argv, envp);
	if (!split_paths)
		exit((clean_all_pipes_also_fd(argc, pipefds, 0)) * -1);
	path = find_path(argv[i + 2], split_paths);
	if (!path)
		exit((clean_all_pipes_also_fd(argc, pipefds, 0)) * -1);
	execve(path, ft_split(argv[i + 2], ' '), NULL);
}

static void	first_command(int pipefds[][2], char **argv, char **envp)
{
	int		argc;
	int		input;
	char	**split_paths;
	char	*path;

	close(pipefds[0][0]);
	argc = count_args(argv);
	input = open(argv[1], O_RDONLY);
	if (input == -1)
		exit((clean_all_pipes_also_fd(argc, pipefds, 0)) * -1);
	if (dup2(input, STDIN_FILENO) == -1)
		exit((clean_all_pipes_also_fd(argc, pipefds, input)) * -1);
	if (dup2(pipefds[0][1], STDOUT_FILENO) == -1)
		exit((clean_all_pipes_also_fd(argc, pipefds, input)) * -1);
	close(input);
	close(pipefds[0][1]);
	split_paths = split_path(argc, argv, envp);
	if (!split_paths)
		exit((clean_all_pipes_also_fd(argc, pipefds, input)) * -1);
	path = find_path(argv[2], split_paths);
	if (!path)
		exit((clean_all_pipes_also_fd(argc, pipefds, input)) * -1);
	execve(path, ft_split(argv[2], ' '), NULL);
}

void	execute_each_command(int index, int pipes[][2], char **argv, char **e)
{
	int	args;

	args = count_args(argv);
	printf("%d %d\n", args, index);
	if (index == 0)
		first_command(pipes, argv, e);
	else if (index > 0 && index < args)
		middle_command(index, pipes, argv, e);
	else if (index == args)
		last_command(pipes, argv, e);
}
