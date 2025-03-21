/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_check_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:39:44 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/21 00:03:27 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	destroy_fork(t_data *data)
{
	free(data->utils.line_heredoc);
	if (data->flags.should_clean)
		clean_process(data);
	free(data->utils.filename);
	exit (0);
}

static int	shoud_break(t_data *data, char *limiter)
{
	return (!data->utils.line_heredoc
		|| !ft_strcmp(data->utils.line_heredoc, limiter));
}

void	heredoc_check_mode(t_data *data, char *limiter, int *fd)
{
	if (*fd < 0)
		exit (1);
	data->utils.line_heredoc = NULL;
	while (1)
	{
		heredoc_signal();
		free(data->utils.line_heredoc);
		data->utils.line_heredoc = readline("> ");
		if (shoud_break(data, limiter))
			break ;
		ft_putendl_fd(data->utils.line_heredoc, *fd);
	}
	close (*fd);
	destroy_fork(data);
}
