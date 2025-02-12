/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-handle_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:43:59 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/11 16:40:36 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(unsigned char c, int flag)
{
	if (flag == 1)
		return ((c != ' ' && c != '&' && c != '|' && c != '(' && c != ')'
				&& c != '<' && c != '>'));
	if (flag == 2)
		return ((c != '&' && c != '|' && c != '(' && c != ')'
				&& c != '<' && c != '>'));
	return ((c != ' ' && c != '&' && c != '|' && c != '(' && c != ')'
			&& c != '<' && c != '>') && !(is_quote(c)));
}

int	handle_word(char *str, t_token **token, t_lex *lex)
{
	int	i;
	int	flag;
	int	j;

	i = 0;
	// if (((is_cmd(lex->word, lex) && lex->id != FD) || lex->id == NONE || ft_strncmp(lex->word, "./", 2) == 0)
	// 	&& ft_strcmp(lex->word, ".") != 0 && ft_strncmp(lex->word, "../", 3) != 0)
	// 	lex->id = CMD;
	// else if (lex->id != FD && lex->id != LIMITER && lex->id != CMD)
	// 	lex->id = ARG;
	get_label(lex);
	flag = 1;
	if ((is_quote(str[i]) || str[i] == '\\'))
		flag = 2;
	j = quote_close(str);
	while (str[i] && is_word(str[i], flag))
		if (i++ - 1 >= 0 && flag == 2
			&& ((str[i] == ' ' && is_quote(str[i - 1]))
			|| (i >= j && str[i] == ' ')))
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
