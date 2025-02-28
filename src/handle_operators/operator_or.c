/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:13:20 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/21 16:26:32 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execute_cmd1(char *cmd1, int *status, char **envp)
{
	int		id;
	char	**split1;

	split1 = ft_split(cmd1, ' ');
	if (!split1)
	{
		*status = -1;
		return ;
	}
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
	waitpid(id, status, 0);
}

static void	execute_cmd2(char *cmd2, int *status, char **envp)
{
	int		id;
	char	**split2;

	split2 = ft_split(cmd2, ' ');
	if (!split2)
	{
		*status = -1;
		return ;
	}
	id = fork();
	if (id == 0)
	{
		if (execve(split2[0], split2, envp) == -1)
		{
			free_splits(NULL, split2, NULL, NULL);
			exit(errno);
		}
	}
	free_splits(NULL, split2, NULL, NULL);
	waitpid(id, status, 0);
}

void	operator_or(char *cmd1, char *cmd2, char **envp)
{
	int	status;

	status = 0;
	execute_cmd1(cmd1, &status, envp);
	if (status == 0)
		return ;
	execute_cmd2(cmd2, &status, envp);
}

/*int	main(int argc, char **argv, char **envp)
{
	if (argc < 2)
		return (1);
	operator_or(argv[1], argv[2], envp);
	return (0);
}*/
