/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:20:41 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/08 20:46:13 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_file(char *f, t_utils *data)
{
	if (access(f, F_OK) != 0)
	{
		ft_printf("Doesn't exist a file\n");
		data->exec_status = 1;
		return (0);
	}
	if (access(f, R_OK) != 0)
	{
		ft_printf("You don't have read permissions\n");
		data->exec_status = 1;
		return (0);
	}
	return (1);
}

void	handle_red_in(char **cmd, char *f, t_utils *data, int flag)
{
	int		id;
	int		fd;

	if (!check_file(f, data))
		return ;
	fd = open(f, O_RDONLY);
	if (fd == -1)
		return ;
	if (flag == 1)
	{
		id = fork();
		if (id == 0)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				exit(1);
			check_errno(cmd, data);
		}
	}
	if (flag == 1 && id != -1)
		waitpid(id, &data->exec_status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	**split1;
	int		index;

	data.utils.exec_status = 0;
	data.utils.envp = envp;
	if (argc < 3)
		return (1);
	split1 = ft_split(argv[1], ' ');
	if (!split1)
		return (1);
	index = 2;
	while (index < argc - 1)
	{
		handle_red_in(split1, argv[index], &data.utils, 0);
		index++;
	}
	handle_red_in(split1, argv[index], &data.utils, 1);
	translate(&data);
	free_splits(NULL, split1, NULL, NULL);
	ft_printf("EXEC STATUS: %d\n", data.utils.exec_status);
	return (0);
}
