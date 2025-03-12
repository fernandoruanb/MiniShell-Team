/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_check_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:39:44 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/12 12:38:34 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_check_mode(t_utils *data, char *limiter, int fd)
{
	data->line_heredoc = NULL;
	while (1)
	{
		data->line_heredoc = NULL;
		heredoc_signal();
		data->line_heredoc = readline("> ");
		if (data->line_heredoc == NULL)
			return ;
		if (ft_strcmp(data->line_heredoc, limiter) == 0)
		{
			free(data->line_heredoc);
			break ;
		}
		ft_putendl_fd(data->line_heredoc, fd);
		free(data->line_heredoc);
	}
}
