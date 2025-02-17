/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-handle_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:43:59 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/17 12:01:09 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_message(char *message, int __return__, t_token **token)
{
	if (message)
		printf("%s\n", message);
	token_clean(*token);
	return (__return__);
}

int	is_word(unsigned char c, int flag)
{
	if (flag == 1)
		return ((c != ' ' && c != '&' && c != '|' && c != '(' && c != ')'
				&& c != '<' && c != '>'));
	if (flag == 2)
		return (c >= 32 && c <= 126);
	return ((c != ' ' && c != '&' && c != '|' && c != '(' && c != ')'
			&& c != '<' && c != '>') && !(is_quote(c)));
}

static int	conditiontobreak(char *str, int j, int i)
{
	return (((i >= j && str[i] == ' ')
			|| (j == 0 && str[i] == ' ' && is_quote(str[i - 1]))));
}

int	handle_word(char *str, t_token **token, t_lex *lex)
{
	int	i;
	int	flag;
	int	j;

	i = 0;
	get_label(lex);
	flag = 1 + (is_quote(str[i]) || str[i] == '\\');
	j = quote_close(str);
	while (str[i] && is_word(str[i], flag))
		if (i++ - 1 >= 0 && flag == 2 && conditiontobreak(str, j, i))
			break ;
	(*token) = token_add((*token),
			token_create(str, i, lex->index++, lex->id), NULL);
	if (((lex->id == CMD || lex->id == FD || lex->id == LIMITER)
			&& ft_strncmp(str, "xargs", 5) != 0))
		lex->id = ARG;
	else if (lex->id == FD)
		lex->id = CMD;
	return (i);
}
