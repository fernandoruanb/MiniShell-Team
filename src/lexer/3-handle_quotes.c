/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-handle_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:44:28 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/11 16:55:09 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(unsigned char c)
{
	return (c == '\'' || c == '\"');
}


// int	handle_quote2(char *str, t_token **token)
// {
// 	char	quote;
// 	int		i;

// 	i = 0;
// 	if (str[i] == '\\')
// 		i++;
// 	quote = str[i++];
// 	while (str[i])
// 		if (str[i++] == quote)
// 			return (i - 1);
// 	token_clean(*token);
// 	(*token) = NULL;
// 	return (-1);
// }

// static int	match_quotes(char *str, int *i)
// {
// 	char	quote;

// 	while (str[*i] && !is_quote(str[*i]))
// 		(*i)++;
// 	if (!str[*i])
// 		return (0);
// 	quote = str[*i];
// 	while (str[++*i])
// 		if (str[*i] == quote)
// 			return (0);
// 	return (1);
// }

int	special_char(char c)
{
	return (c == '?' || c == '$' || c == '\\' || c == '/' || is_quote(c) || c == '*');
}

// int	handle_quote(char *str, t_token **token)
// {
// 	int		i;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		i = quote_close(&str[i]);
// 		if (i < 0)
// 			return (bad_quotes(token));
// 	}
// 	i = -1;
// 	while (str[++i])
// 		if (str[i] == '\\' && !special_char(str[i + 1]))
// 			return (bad_quotes(token));
// 	return (1);
// }

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


// static int	make_token(t_token **token, char *str, t_lex *lex, int *i)
// {
// 	(*token) = token_add((*token),
// 			token_create(str, *i, lex->index++, lex->id), NULL);
// 	if (lex->id == FD || lex->id == LIMITER)
// 		lex->id = ARG;
// 	return (*i);
// }

int	count_quotes(char *str, t_token **token)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	while (str[++i])
	{
		if (str[i] == '\\')
		{
			i++;
			continue ;
 		}
		if (is_quote(str[i]))
			cnt++;
	}
	if (cnt % 2 != 0)
	{
		token_clean(*token);
		(*token) = NULL;
		return (1);
	}
	return (0);
}
