/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-handle_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:44:28 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/07 11:25:06 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(unsigned char c)
{
	return (c == '\'' || c == '\"' || c == '\\');
}

static int	make_token(t_token **token, char *str, t_lex *lex, int *i)
{
	(*token) = token_add((*token),
			token_create(str, *i, lex->index++, lex->id), NULL);
	if (lex->id == FD || lex->id == LIMITER)
		lex->id = ARG;
	return (*i);
}

int	handle_quote(char *str, t_token **token, t_lex *lex)
{
	char	quote;
	int		i;

	i = 0;
	if (lex->id == NONE)
		lex->id = CMD;
	else if (lex->id == CMD)
		lex->id = ARG;
	if (str[i] == '\\')
		i++;
	quote = str[i++];
	while (str[i])
		if (str[i++] == quote)
			return (make_token(token, str, lex, &i));
	if (str[0] == '\\')
		return (make_token(token, str, lex, &i));
	token_clean(*token);
	(*token) = NULL;
	return (-1);
}

int	handle_bracket(char *str, t_token **token, t_lex *lex)
{
	if (str[0] == '(')
		(*token) = token_add((*token),
				token_create(str, 1, lex->index++, BRACKET_O), NULL);
	if (str[0] == ')')
		(*token) = token_add((*token),
				token_create(str, 1, lex->index++, BRACKET_C), NULL);
	lex->id = CMD;
	return (1);
}
