/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:22:17 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/30 14:47:08 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	*add_token(t_data *data, t_tokens *new)
{
	int	index;
	t_tokens	*last;

	if (data->tokens == NULL)
	{
		data->tokens = new;
		new->index = 0;
	}
	else
	{
		index = 0;
		last = data->tokens;
		while (last->next != NULL)
		{
			index++;
			last = last->next;
		}
		last->next = new;
		new->prev = last;
		new->index = index;
	}
}
