/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   godness_decision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:42:38 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/16 13:43:21 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	godness_decision(int flag, t_utils *data)
{
	if (flag == 2)
	{
		data->status = 1;
		return (1);
	}
	return (0);
}
