/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:20:41 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/10 14:04:08 by jopereir         ###   ########.fr       */
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

int	handle_red_in(char *f, t_utils *data)
{
	int		fd;

	if (!check_file(f, data) || check_is_directory_fd(f, data))
		return (INT_MIN);
	fd = open(f, O_RDONLY);
	return (fd);
}

/*int	main(int argc, char **argv, char **envp)
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
		if (handle_red_in(split1, argv[index], &data.utils, 0))
			return (1);
		index++;
	}
	if (handle_red_in(split1, argv[index], &data.utils, 1))
		return (1);
	translate(&data);
	free_splits(NULL, split1, NULL, NULL);
	ft_printf("EXEC STATUS: %d\n", data.utils.exec_status);
	return (0);
}*/
