/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:41:58 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/20 09:09:23 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipes_case(t_token *root, t_utils *data)
{
	t_token	*last;
	int		flag;

	flag = 0;
	last = root;
	while (last->previous)
	{
		if (last->id == PIPE || last->id == OPERATOR_AND
			|| last->id == OPERATOR_OR)
		{
			flag = 2;
			break ;
		}
		last = last->previous;
	}
	return (godness_decision(flag, data));
}
