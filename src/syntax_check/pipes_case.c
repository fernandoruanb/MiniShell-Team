/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:41:58 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/19 12:04:39 by fruan-ba         ###   ########.fr       */
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
		if (last->id == PIPE)
		{
			flag = 2;
			break ;
		}
		last = last->previous;
	}
	/*last = root;
	while (last->next)
	{
		if (last->id == PIPE)
		{
			flag++;
			break ;
		}
		last = last->next;
	}*/
	return (godness_decision(flag, data));
}
