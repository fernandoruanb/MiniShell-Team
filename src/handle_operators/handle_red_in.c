/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:20:41 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/21 16:10:24 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* ATUALIZAR FUNCIONALIDADE */

int	check_file(char *filename, int *status)
{
	if (access(filename, F_OK) != 0)
	{
		*status = 1;
		return (0);
	}
	if (access(filename, R_OK) != 0)
	{
		*status = 126;
		return (0);
	}
	return (1);
}

void	handle_red_in(char *cmd1, char *filename, int *status, char **envp)
{
	int		id;
	int		fd;
	char	**split1;

	if (!check_file(filename, status))
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
	{
		if (execve(split1[0], split1, envp) == -1)
		{
			free_splits(NULL, split1, NULL, NULL);
			exit(errno);
		}
	}
	free_splits(NULL, split1, NULL, NULL);
	close(fd);
	waitpid(id, status, 0);
}

/*int	main(int argc, char **argv, char **envp)
{
	int	status;

	if (argc < 3)
		return (1);
	status = 0;
	handle_red_in(argv[1], argv[2], &status, envp);
	return (0);
}*/
