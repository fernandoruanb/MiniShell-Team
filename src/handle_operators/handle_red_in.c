/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:20:41 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/28 14:14:36 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_file(char *filename, t_utils *data)
{
	if (access(filename, F_OK) != 0)
	{
		data->exec_status = 1;
		return (0);
	}
	if (access(filename, R_OK) != 0)
	{
		data->exec_status = 1;
		return (0);
	}
	return (1);
}

void	handle_red_in(char *cmd1, char *filename, t_utils *data)
{
	int		id;
	int		fd;
	char	**split1;

	if (!check_file(filename, data))
		return ;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ;
	split1 = ft_split(cmd1, ' ');
	if (!split1)
		return ;
	dup2(fd, STDIN_FILENO);
	id = fork();
	if (id == 0)
		check_errno(split1, data);
	free_splits(NULL, split1, NULL, NULL);
	close(fd);
	waitpid(id, &data->exec_status, 0);
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
