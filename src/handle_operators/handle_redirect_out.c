/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect_out.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:55:51 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/05 16:55:49 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*capture_dir(char *filename);

static char	*initialize_directory(char *filename, t_utils *data)
{
	char	*detect_dir;

	detect_dir = capture_dir(filename);
	if (detect_dir == NULL)
	{
		detect_dir = ft_strdup(".");
		if (!detect_dir)
			return (NULL);
	}
	if (detect_dir != NULL)
	{
		if (access(detect_dir, W_OK) == -1)
		{
			data->exec_status = 1;
			free(detect_dir);
			return (NULL);
		}
	}
	return (detect_dir);
}

static char	*capture_dir(char *filename)
{
	int		index;
	int		limit;
	char	*detect_dir;

	index = 0;
	limit = 0;
	while (filename[index] != '\0')
	{
		if (filename[index] == '/')
			limit = index;
		index++;
	}
	if (limit != 0)
		detect_dir = ft_substr(filename, 0, limit);
	else
		detect_dir = NULL;
	if (!detect_dir)
		return (NULL);
	return (detect_dir);
}

void	handle_redirect_out(char *filename, t_utils *data)
{
	int		fd;
	char	*detect_dir;

	detect_dir = initialize_directory(filename, data);
	if (detect_dir == NULL)
		return ;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(detect_dir);
		return ;
	}
	//ft_putendl_fd(message, fd);
	dup2(fd, STDOUT_FILENO);
	close (fd);
	free(detect_dir);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	data;
// 	int		fd;

// 	data.utils.exec_status = 0;
// 	data.utils.envp = envp;
// 	if (argc != 3)
// 		return (1);
// 	fd = -1;
// 	if (fd == -1)
// 		return (1);
// 	dup2(fd, STDOUT_FILENO);
// 	handle_redirect_out(argv[1], argv[2], &data.utils);
// 	ft_printf("EXEC STATUS: %d\n", data.utils.exec_status);
// 	return (0);
// }
