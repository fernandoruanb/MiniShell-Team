/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:50:15 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/13 14:01:49 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	translate(t_data *data)
{
	if (data->utils.exec_status == 32512)
		data->utils.exec_status = 127;
	else if (data->utils.exec_status == 2)
		data->utils.exec_status = 130;
	else if (data->utils.exec_status == 32256
		|| data->utils.exec_status == 3328)
		data->utils.exec_status = 126;
	else if (data->utils.exec_status == 256
		|| data->utils.exec_status == 512)
		data->utils.exec_status = 2;
}
