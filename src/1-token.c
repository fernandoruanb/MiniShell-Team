/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:13:59 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/10 10:47:12 by jopereir         ###   ########.fr       */
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
	if (token)
		free(token);
}

/*
	Temporaria, apagar ela antes de mandar
*/
void	token_print(t_token *token)
{
	if (!token)
		return ;
	if (token->id == CMD)
		printf("Token %d: %s Tipo: CMD\n", token->index, token->str);
	else if (token->id == PIPE)
		printf("Token %d: %s Tipo: PIPE\n", token->index, token->str);
	else if (token->id == REDIRECT_IN)
		printf("Token %d: %s Tipo: REDIRECT_IN\n", token->index, token->str);
	else if (token->id == REDIRECT_OUT)
		printf("Token %d: %s Tipo: REDIRECT_OUT\n", token->index, token->str);
	else if (token->id == ARG)
		printf("Token %d: %s Tipo: ARG\n", token->index, token->str);
	else if (token->id == HEREDOC)
		printf("Token %d: %s Tipo: HEREDOC\n", token->index, token->str);
	else if (token->id == APPEND)
		printf("Token %d: %s Tipo: APPEND\n", token->index, token->str);
	else if (token->id == FD)
		printf("Token %d: %s Tipo: FD\n", token->index, token->str);
	else if (token->id == LIMITER)
		printf("Token %d: %s Tipo: LIMITER\n", token->index, token->str);
	else if (token->id == OPERATOR_AND)
		printf("Token %d: %s Tipo: OPERATOR_AND\n", token->index, token->str);
	else if (token->id == OPERATOR_OR)
		printf("Token %d: %s Tipo: OPERATOR_OR\n", token->index, token->str);
	else if (token->id == BRACKET_O)
		printf("Token %d: %s Tipo: BRACKET_O\n", token->index, token->str);
	else if (token->id == BRACKET_C)
		printf("Token %d: %s Tipo: BRACKET_C\n", token->index, token->str);
	token_print(token->next);
}
