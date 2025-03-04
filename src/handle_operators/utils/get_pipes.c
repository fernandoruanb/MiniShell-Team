/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:29:46 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/24 10:26:44 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	get_pipes(t_token *root)
{
	t_token	*last;
	int		count;

	if (!root)
		return (0);
	last = root;
	count = 0;
	while (last->next)
	{
		if (last->id == PIPE)
			count++;
		last = last->next;
	}
	return (count);
}
