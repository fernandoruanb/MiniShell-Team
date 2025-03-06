/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:20:41 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/06 12:26:45 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_file(char *filename, t_utils *data)
{
	if (access(filename, F_OK) != 0)
	{
		ft_printf("Doesn't exist a file\n");
		data->exec_status = 1;
		return (0);
	}
	if (access(filename, R_OK) != 0)
	{
		ft_printf("You don't have read permissions\n");
		data->exec_status = 1;
		return (0);
	}
	return (1);
}

int	handle_red_in(char *filename, t_utils *data)
{
	// int		id;
	int		fd;

	if (!check_file(filename, data))
		return (-1);
	fd = open(filename, O_RDONLY);
	// if (fd == -1)
	// 	return (-1);
	// if (dup2(fd, STDIN_FILENO) == -1)
	// 	return ;
	// id = fork();
	// if (id == 0)
	// 	check_errno(cmd1, data);
	// free_splits(NULL, cmd1, NULL, NULL);
	// if (fd > 2)
	// 	close(fd);
	// waitpid(id, &data->exec_status, 0);
	return (fd);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.utils.exec_status = 0;
	data.utils.envp = envp;
	if (argc < 3)
		return (1);
	handle_red_in(argv[1], argv[2], &data.utils);
	translate(&data.utils);
	ft_printf("EXEC STATUS: %d\n", data.utils.exec_status);
	return (0);
}*/
