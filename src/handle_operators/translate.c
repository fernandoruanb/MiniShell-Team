/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:50:15 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/05 16:10:39 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	translate(t_utils *data)
{
	if (data->exec_status == 32512)
		data->exec_status = 127;
	else if (data->exec_status == 32256 || data->exec_status == 3328)
		data->exec_status = 126;
	else if (data->exec_status == 256 || data->exec_status == 512)
		data->exec_status = 2;
}
