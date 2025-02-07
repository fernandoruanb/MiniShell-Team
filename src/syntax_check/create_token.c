/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:02:55 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 13:03:07 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_token(char *str, t_id id)
{
	static int	index = 0;
	t_token		*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	index++;
	new_token->str = str;
	new_token->index = index;
	new_token->id = id;
	new_token->next = NULL;
	new_token->previous = NULL;
	return (new_token);
}
