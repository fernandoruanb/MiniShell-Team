/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect_out.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:55:51 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/14 10:40:57 by jonas            ###   ########.fr       */
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
	{
		detect_dir = ft_substr(f, 0, limit);
		if (!detect_dir)
			return (NULL);
	}
	else
		detect_dir = NULL;
	return (detect_dir);
}

int	handle_redirect_out(char *f, t_utils *data)
{
	int		fd;
	char	*detect_dir;

	detect_dir = initialize_directory(f, data);
	if (check_is_directory_fd(f, data))
		return (INT_MIN);
	if (detect_dir == NULL)
		return (INT_MIN);
	fd = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(detect_dir);
	return (fd);
}

// int	main(int argc, char **argv, char **envp)
// {
//  	t_data	data;
//  	int		fd;
// 	char	**split1;
// 	int	index;

//  	data.utils.exec_status = 0;
//  	data.utils.envp = envp;
// 	split1 = ft_split(argv[1], ' ');
// 	(void)argc;
// 	index = 2;
// 	if (!split1)
// 		return (1);
// 	while (index < argc - 1)
// 	{
//  		handle_redirect_out(split1, argv[index], &data.utils, 0);
// 		index++;
// 	}
// 	handle_redirect_out(split1, argv[index], &data.utils, 1);
// 	free_splits(NULL, split1, NULL, NULL);
// 	translate(&data);
//  	ft_printf("EXEC STATUS: %d\n", data.utils.exec_status);
//  	return (0);
// }
