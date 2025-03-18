/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:05:05 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/18 10:21:57 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*capture_dir(char *f);

static char	*initialize_directory(char *f, t_utils *data)
{
	char	*detect_dir;

	detect_dir = capture_dir(f);
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

static char	*capture_dir(char *f)
{
	int		index;
	int		limit;
	char	*detect_dir;

	index = 0;
	limit = 0;
	while (f[index] != '\0')
	{
		if (f[index] == '/')
			limit = index;
		index++;
	}
	if (limit != 0)
		detect_dir = ft_substr(f, 0, limit);
	else
		detect_dir = ft_strdup(".");
	if (!detect_dir)
		return (NULL);
	return (detect_dir);
}

int	append(char *f, t_utils *data)
{
	int			fd;
	char		*detect_dir;

	detect_dir = initialize_directory(f, data);
	if (check_is_directory_fd(f, data) || check_invalid_permission(f, 1))
	{
		free(detect_dir);
		data->exec_status = 1;
		return (INT_MIN);
	}
	if (detect_dir == NULL)
		return (INT_MIN);
	fd = open(f, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(detect_dir);
	return (fd);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	**split1;
	int		index;

	data.utils.exec_status = 0;
	data.utils.envp = envp;
	(void)argc;
	split1 = ft_split(argv[1], ' ');
	if (!split1)
		return (1);
	index = 2;
	while (index < argc - 1)
	{
		append(split1, argv[index], &data.utils, 0);
		index++;
	}
	append(split1, argv[index], &data.utils, 1);
	free_splits(NULL, split1, NULL, NULL);
	ft_printf("EXEC STATUS: %d\n", data.utils.exec_status);
	return (0);
}*/
