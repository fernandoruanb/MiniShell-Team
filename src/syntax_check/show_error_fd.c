/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_error_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:51:41 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/13 21:46:43 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	show_error_fd(char *message, int flag, t_utils *data, int signal)
{
	ft_putendl_fd(message, 2);
	if (signal != 0)
	{
		data->exit_status = signal;
		data->exec_status = signal;
	}
	if (flag == 1)
		return (1);
	return (0);
}
