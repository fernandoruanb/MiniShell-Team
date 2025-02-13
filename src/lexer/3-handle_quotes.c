/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-handle_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:44:28 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/13 12:03:49 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(unsigned char c)
{
	return (c == '\'' || c == '\"');
}

int	quote_close(char *str)
{
	int		i;
	char	quote;

	if (!str)
		return (0);
	i = 0;
	quote = '\0';
	if (is_quote(str[i]))
		quote = str[i++];
	while (str[i++] && quote)
		if (str[i] == quote)
			return (i);
	return (0);
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
