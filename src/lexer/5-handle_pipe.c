/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-handle_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:41:29 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/11 16:52:25 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_close(char *str)
{
	int		i;
	char	quote;

	i = -1;
	quote = '\0';
	while (str[++i])
	{
		if (is_quote(str[i]))
		{
			quote = str[i];
			break ;
		}
	}
	if (!quote)
		return (i);
	while (str[i])
		if (str[i++] == quote)
			return (i);
	return (-1);
}

static int	handle_or(char *str, t_token **token, t_lex *lex)
{
	(*token) = token_add((*token),
			token_create(str, 2, lex->index++, OPERATOR_OR), NULL);
	lex->id = CMD;
	return (2);
}

int	handle_pipe(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != '|')
			break ;
	if (i == 2)
		return (handle_or(str, token, lex));
	if (i > 2)
	{
		token_clean(*token);
		return (-1);
	}
	else
		(*token) = token_add((*token),
				token_create(str, i, lex->index++, PIPE), NULL);
	lex->id = CMD;
	return (i);
}
