/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_and.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:48:08 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/27 10:53:42 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execute_cmd1(char *cmd1, t_utils *data)
{
	int		id;
	char	**split1;

	split1 = ft_split(cmd1, ' ');
	if (!split1)
		return ;
	id = fork();
	if (id == 0)
		check_errno(split1, data);
	if (split1 != NULL)
		free_splits(NULL, split1, NULL, NULL);
	waitpid(id, &data->exec_status, 0);
}

static void	execute_cmd2(char *cmd2, t_utils *data)
{
	int		id;
	char	**split2;

	split2 = ft_split(cmd2, ' ');
	if (!split2)
		return ;
	id = fork();
	if (id == 0)
		check_errno(split2, data);
	if (split2 != NULL)
		free_splits(NULL, split2, NULL, NULL);
	waitpid(id, &data->exec_status, 0);
}

void	operator_and(char *cmd1, char *cmd2, t_utils *data)
{
	execute_cmd1(cmd1, data);
	if (data->exec_status != 0)
		return ;
	execute_cmd2(cmd2, data);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.utils.exec_status = 0;
	data.utils.envp = envp;
	if (argc < 2)
		return (1);
	operator_and(argv[1], argv[2], &data.utils);
	translate(&data.utils);
	ft_printf("EXEC STATUS: %d\n", data.utils.exec_status);
	return (0);
}*/
