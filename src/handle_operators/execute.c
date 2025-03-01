/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:15:34 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/01 18:58:52 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_data	data;

	data.utils.exec_status = 0;
	data.utils.envp = envp;

/*	ft_printf("TEST 01: ls\n\n");
	single_command("/bin/ls", &data.utils);	
	translate(&data.utils);
	ft_printf("EXEC_STATUS: %d\n\n", data.utils.exec_status);

	ft_printf("TEST 02: ls -l\n\n");
	single_command("/bin/ls -l", &data.utils);
	translate(&data.utils);
	ft_printf("EXEC_STATUS: %d\n", data.utils.exec_status);

	ft_printf("TEST 03: ls -l -a\n\n");
	single_command("/bin/ls -l -a", &data.utils);
	translate(&data.utils);
	ft_printf("EXEC STATUS: %d\n", data.utils.exec_status);

	ft_printf("TEST 04: echo \'\n\n");
	single_command("/bin/echo \'", &data.utils);
	translate(&data.utils);
	ft_printf("EXEC_STATUS: %d\n", data.utils.exec_status);

	ft_printf("TEST 05: echo \"\"\n\n");
	single_command("/bin/echo \"\"", &data.utils);
	translate(&data.utils);
	ft_printf("EXEC_STATUS: %d\n", data.utils.exec_status);

	ft_printf("TEST 06: \"\'\"\n\n");
	single_command("/bin/echo \"\'\"", &data.utils);
	translate(&data.utils);
	ft_printf("EXEC_STATUS: %d\n", data.utils.exec_status);

	ft_printf("TEST 07: ls -l\n\n");
	single_command("/bin/ls -l", &data.utils);
	translate(&data.utils);
	ft_printf("EXEC_STATUS: %d\n", data.utils.exec_status);

	ft_printf("TEST 08: echo oi | cat -n | wc -c\n\n");
	handle_pipe_op("/bin/echo oi", 1, &data.utils);
	handle_pipe_op("/bin/cat -n", 3, &data.utils);
	handle_pipe_op("/bin/wc -c", 2, &data.utils);
	translate(&data.utils);
	ft_printf("EXEC_STATUS: %d\n", data.utils.exec_status); */
	ft_printf("TEST 09: cat | cat | cat | ls\n\n");
	handle_pipe_op("/bin/cat", 1, &data.utils);
//	handle_pipe_op("/bin/cat", 3, &data.utils);
//	handle_pipe_op("/bin/cat", 3, &data.utils);
	handle_pipe_op("/bin/ls", 2, &data.utils);
	translate(&data.utils);
	ft_printf("EXEC_STATUS: %d\n", data.utils.exec_status);
	return (0);
}
