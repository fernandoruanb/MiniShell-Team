/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:13:59 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/20 16:40:14 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_create(char *str, int n, int index, t_id id)
{
	t_token	*new;

	new = calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strndup(str, n);
	new->id = id;
	new->next = NULL;
	new->previous = NULL;
	new->index = index;
	return (new);
}

t_token	*token_add(t_token *token, t_token *new, t_token *prev)
{
	if (!token)
	{
		new->previous = prev;
		return (new);
	}
	token->next = token_add(token->next, new, token);
	return (token);
}

void	token_clean(t_token *token)
{
	if (!token)
		return ;
	token_clean(token->next);
	if (token->str)
		free(token->str);
	free(token);
	token = NULL;
}
