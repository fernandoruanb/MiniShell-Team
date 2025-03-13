/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_check_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:39:44 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/13 16:35:48 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_check_mode(t_utils *data, char *limiter, int *fd)
{
	if (*fd < 0)
		return ;
	data->line_heredoc = NULL;
	while (1)
	{
		heredoc_signal();
		free(data->line_heredoc);
		data->line_heredoc = readline("> ");
		if (!data->line_heredoc)
			break ;
		if (!ft_strcmp(data->line_heredoc, limiter))
			break ;
		ft_putendl_fd(data->line_heredoc, *fd);
	}
	close (*fd);
	*fd = open(data->filename, O_RDONLY);
}
