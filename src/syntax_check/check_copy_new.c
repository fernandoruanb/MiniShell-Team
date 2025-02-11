/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_copy_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:32:59 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/11 13:33:11 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_copy_new(t_utils *data)
{
	if (data->copy_new)
	{
		free(data->copy_new);
		data->copy_new = NULL;
	}
}
