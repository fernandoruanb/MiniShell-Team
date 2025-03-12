/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:11:40 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/12 14:10:11 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	free_strs(char *str1, char *str2)
{
	free(str1);
	free(str2);
	return (-1);
}

// static void	close_fd(int fd)
// {
// 	close(fd);
// }

// static void	delete_heredoc(char *filename)
// {
// 	int		pid;
// 	char	*target;
// 	char	**split2;

// 	target = ft_strjoin("/bin/rm -- ", filename);
// 	if (!target)
// 		return ;
// 	split2 = ft_split(target, ' ');
// 	if (!split2)
// 	{
// 		free(target);
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (execve("/bin/rm", split2, NULL) == -1)
// 		{
// 			free_splits(target, split2, NULL, NULL);
// 			exit(errno);
// 		}
// 	}
// 	free_splits(target, split2, NULL, NULL);
// 	waitpid(pid, NULL, 0);
// }

// static void	execute_heredoc(char *filename)
// {
// 	//int		pid;
// 	int		fd;

// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		return ;
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 		return (close_fd(fd));
// 	// pid = fork();
// 	// if (pid == 0)
// 	// 	check_errno(cmd, data);
// 	// close(fd);
// 	// waitpid(pid, &data->exec_status, 0);
// 	// return (0);
// }

int	heredoc(char *limiter, t_utils *data)
{
	int		fd;
//	char	*line;
	int	pid;

	//line = NULL;
	data->exec_status = 0;
	data->filename = ft_strjoin("/tmp/", limiter);
	if (!data->filename)
		return (-1);
	fd = open(data->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (free_strs(data->filename, NULL));
	pid = fork();
	if (pid == -1)
	{
		close(fd);
		return (-1);
	}
	if (pid == 0)
		heredoc_check_mode(data, limiter, fd);
	close(fd);
	waitpid(pid, &data->exec_status, 0);
	fd = open(data->filename, O_RDONLY);
	free(data->filename);
	return (fd);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	**cmd;
	int	index;

	data.utils.exec_status = 0;
	data.utils.envp = envp;
	(void)argc;
	cmd = ft_split(argv[1], ' ');
	if (!cmd)
		return (1);
	index = 2;
	while (index < argc - 1)
	{
		heredoc(cmd, argv[index], &data.utils, 0);
		index++;
	}
	heredoc(cmd, argv[index], &data.utils, 1);
	translate(&data);
	return (0);
}*/
