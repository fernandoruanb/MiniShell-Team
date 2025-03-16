/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:20:41 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/16 12:46:06 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_file(char *f, t_utils *data)
{
	if (access(f, F_OK) != 0)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		data->exec_status = 1;
		return (0);
	}
	if (access(f, R_OK) != 0)
	{
		ft_putstr_fd("You don't have read permissions\n", 2);
		data->exec_status = 1;
		return (0);
	}
	return (1);
}

static char	*remove_all_quotes(char *filename)
{
	char	*buffer;
	size_t	length;
	int		index;
	int		count;

	length = ft_strlen(filename);
	if (length == 0)
		return (NULL);
	buffer = (char *)malloc(length + 1);
	if (!buffer)
		return (NULL);
	index = 0;
	count = 0;
	while (filename[index] != '\0')
	{
		if (filename[index] != '\'' && filename[index] != '\"')
		{
			buffer[count] = filename[index];
			count++;
		}
		index++;
	}
	buffer[count] = '\0';
	return (buffer);
}

int	handle_red_in(char *f, t_utils *data)
{
	int			fd;
	char		*true_archive;

	true_archive = remove_all_quotes(f);
	if (!true_archive)
		return (INT_MIN);
	f = true_archive;
	if (!check_file(f, data) || check_is_directory_fd(f, data))
	{
		free(f);
		return (INT_MIN);
	}
	fd = open(f, O_RDONLY);
	free(f);
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
