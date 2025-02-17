/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:13:59 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/17 17:56:10 by jopereir         ###   ########.fr       */
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
	token = NULL;
}

/*
	Temporaria, apagar ela antes de mandar
*/
void	token_print(t_token *token)
{
	if (!token)
		return ;
	if (token->id == CMD)
		printf("\033[33mToken\033[0m %d: %s \033[33mTipo:\033[0m CMD\n", token->index, token->str);
	else if (token->id == PIPE)
		printf("\033[33mToken\033[0m %d: %s \033[33mTipo:\033[0m PIPE\n", token->index, token->str);
	else if (token->id == REDIRECT_IN)
		printf("\033[33mToken\033[0m %d: %s \033[33mTipo:\033[0m REDIRECT_IN\n", token->index, token->str);
	else if (token->id == REDIRECT_OUT)
		printf("\033[33mToken\033[0m %d: %s \033[33mTipo:\033[0m REDIRECT_OUT\n", token->index, token->str);
	else if (token->id == ARG)
		printf("\033[33mToken\033[0m %d: %s \033[33mTipo:\033[0m ARG\n", token->index, token->str);
	else if (token->id == HEREDOC)
		printf("\033[33mToken\033[0m %d: %s \033[33mTipo:\033[0m HEREDOC\n", token->index, token->str);
	else if (token->id == APPEND)
		printf("\033[33mToken\033[0m %d: %s \033[33mTipo:\033[0m APPEND\n", token->index, token->str);
	else if (token->id == FD)
		printf("\033[33mToken\033[0m %d: %s \033[33mTipo:\033[0m FD\n", token->index, token->str);
	else if (token->id == LIMITER)
		printf("\033[33mToken\033[0m %d: %s \033[33mTipo:\033[0m LIMITER\n", token->index, token->str);
	else if (token->id == OPERATOR_AND)
		printf("\033[33mToken\033[0m %d: %s \033[33mTipo:\033[0m OPERATOR_AND\n", token->index, token->str);
	else if (token->id == OPERATOR_OR)
		printf("\033[33mToken\033[0m %d: %s \033[33mTipo:\033[0m OPERATOR_OR\n", token->index, token->str);
	else if (token->id == BRACKET_O)
		printf("\033[33mToken\033[0m %d: %s \033[33mTipo:\033[0m BRACKET_O\n", token->index, token->str);
	else if (token->id == BRACKET_C)
		printf("\033[33mToken\033[0m %d: %s \033[33mTipo:\033[0m BRACKET_C\n", token->index, token->str);
	token_print(token->next);
}
