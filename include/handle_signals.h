/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:24:17 by jonas             #+#    #+#             */
/*   Updated: 2025/03/13 22:24:48 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_SIGNALS_H
# define HANDLE_SIGNALS_H

# include "minishell.h"

void	handle_prompt_signal(void);
void	heredoc_signal(void);
void	handle_command_signal(void);
t_data	*get_minishell(void);

#endif
