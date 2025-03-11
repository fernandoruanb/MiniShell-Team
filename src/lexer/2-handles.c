/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-handles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:40:26 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/11 18:02:28 by jonas            ###   ########.fr       */
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

	i = 0;
	while (str[i] && str[i] == '>')
		i++;
	if (i == 2)
		return (handle_append(str, token, lex));
	if (i > 2)
		return (error_message("Error:\n\nToo many great signs.\n", -1, token));
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

	i = 0;
	while (str[i] && str[i] == '<')
		i++;
	if (i == 2)
		return (handle_heredoc(str, token, lex));
	if (i > 2)
		return (error_message("Error:\n\nToo many less signs.\n", -1, token));
	(*token) = token_add((*token),
			token_create(str, i, lex->index++, REDIRECT_IN), NULL);
	lex->id = FD;
	return (i);
}

int	handle_and(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '&')
		i++;
	if (i > 2 || i < 2)
		return (error_message("Error:\n\nInvalid number of ampersands '&'.\n", -1, token));
	(*token) = token_add((*token),
			token_create(str, i, lex->index++, OPERATOR_AND), NULL);
	lex->id = CMD;
	return (i);
}
