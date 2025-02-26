/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_check_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:39:44 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/26 18:48:50 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_check_mode(char *line, char *limiter, int fd)
{
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		else
			ft_putendl_fd(line, fd);
	}
}
