/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:27:50 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/04 18:04:13 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	heredoc_sig_cmd(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		exit(130);
	}
}

void	heredoc_signal(void)
{
	signal(SIGINT, heredoc_sig_cmd);
	signal(SIGQUIT, SIG_IGN);
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
