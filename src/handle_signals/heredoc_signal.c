/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:27:50 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/13 12:42:50 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	heredoc_sig_cmd(int signal)
{
	t_data	*minishell;

	if (signal == SIGINT)
	{
		printf("detectei cntrl c\n");
		ft_putchar_fd('\n', 1);
		minishell = get_minishell();
		// call_clean(minishell, 1);
		// clean_program(&minishell->utils);
		clean_process(minishell);
		free(minishell->utils.filename);
		//minishell->prompt->exit_status = 130;
		minishell->utils.exec_status = 130;
		exit(130);
	}
}

void	heredoc_signal(void)
{
	signal(SIGINT, heredoc_sig_cmd);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.utils.exec_status = 0;
	heredoc_signal();
	heredoc(argv[1], argv[2], &data.utils);
	if (data.utils.exec_status == 3584)
		data.utils.exec_status = 0;
	if (data.utils.exec_status == 32512)
		data.utils.exec_status = 127;
	if (data.utils.exec_status == 32256)
	       data.utils.exec_status = 126;	
	ft_printf("EXEC STATUS: %d\n", data.utils.exec_status);
	return (0);
}*/
