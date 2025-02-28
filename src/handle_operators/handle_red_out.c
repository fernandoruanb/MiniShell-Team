/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 08:09:42 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/28 13:47:09 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*capture_dir(char *filename)
{
	int	index;
	int	limit;
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

void	handle_redirect_out(char *message, char *filename, t_utils *data)
{
	int		fd;
	char	*detect_dir;

	detect_dir = capture_dir(filename);
	if (detect_dir == NULL)
		detect_dir = ".";
	if (detect_dir != NULL)
	{
		if (access(detect_dir, W_OK) == -1)
		{
			data->exec_status = 1;
			free(detect_dir);
			return ;
		}
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(detect_dir);
		return ;
	}
	ft_putendl_fd(message, fd);
	if (fd > 2)
		close(fd);
	free(detect_dir);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.utils.exec_status = 0;
	data.utils.envp = envp;
	if (argc != 3)
		return (1);
	handle_redirect_out(argv[1], argv[2], &data.utils);
	ft_printf("EXEC STATUS: %d\n", data.utils.exec_status);
	return (0);
}*/
