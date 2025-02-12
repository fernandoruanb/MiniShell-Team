/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-handles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:40:26 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/07 11:24:53 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_append(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = 2;
	(*token) = token_add((*token),
			token_create(str, i, lex->index++, APPEND), NULL);
	lex->id = FD;
	return (i);
}

int	handle_great(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != '>')
			break ;
	if (i == 2)
		return (handle_append(str, token, lex));
	if (i > 2)
	{
		printf("Lexer: Too many great signs.\n");
		token_clean(*token);
		return (-1);
	}
	else
		(*token) = token_add((*token),
				token_create(str, i, lex->index++, REDIRECT_OUT), NULL);
	lex->id = FD;
	return (i);
}

static int	handle_heredoc(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = 2;
	(*token) = token_add((*token),
			token_create(str, i, lex->index++, HEREDOC), NULL);
	lex->id = LIMITER;
	return (i);
}

int	handle_less(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != '<')
			break ;
	if (i == 2)
		return (handle_heredoc(str, token, lex));
	if (i > 2)
	{
		printf("Lexer: Too many less signs.\n");
		token_clean(*token);
		return (-1);
	}
	else
		(*token) = token_add((*token),
				token_create(str, i, lex->index++, REDIRECT_IN), NULL);
	lex->id = FD;
	return (i);
}

int	handle_and(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != '&')
			break ;
	if (i == 2)
		(*token) = token_add((*token),
				token_create(str, i, lex->index++, OPERATOR_AND), NULL);
	else if (i > 2 || i < 2)
	{
		printf("Lexer: Invalid number of ampersands.\n");
		token_clean(*token);
		(*token) = NULL;
		return (-1);
	}
	lex->id = CMD;
	return (i);
}
