/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:37:34 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/20 16:57:01 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bad_char(t_token **token)
{
	token_clean(*token);
	return (1);
}

static int	handle_special(char *str, t_token **token)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\\')
			return (bad_char(token));
	return (0);
}

char	*get_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_word(str[i], 1))
		i++;
	return (ft_strndup(str, i));
}

static int	handler(char *str, int *i, t_lex *lex, t_token **token)
{
	int	__return__;

	__return__ = 0;
	lex->word = get_str(&str[*i]);
	handle_empty(lex, i, str);
	if (handle_fd(&str[*i]))
		lex->id = FD;
	if (is_word(str[*i], 1))
		__return__ = handle_word(&str[*i], token, lex);
	if (str[*i] == '|')
		__return__ = handle_pipe(&str[*i], token, lex);
	if (str[*i] == '>')
		__return__ = handle_great(&str[*i], token, lex);
	if (str[*i] == '<')
		__return__ = handle_less(&str[*i], token, lex);
	if (str[*i] == '&' || str[*i] == ';')
		__return__ = handle_and(&str[*i], token, lex);
	if (str[*i] == '(' || str[*i] == ')')
		__return__ = handle_bracket(&str[*i], token, lex);
	if (__return__ > 0)
		*i += __return__;
	else
		(*i)++;
	free(lex->word);
	return (__return__);
}

t_token	*lexer(char *str, char **envp)
{
	int		i;
	t_token	*token;
	t_lex	lex;

	if (!str)
		return (NULL);
	i = 0;
	lex.index = 0;
	lex.id = NONE;
	lex.word = NULL;
	lex.envp = envp;
	token = NULL;
	if (handle_special(str, &token))
	{
		printf("Error:\n\n';' or '\\' or '||' or '()' or '&' detected.\n\n");
		return (NULL);
	}
	while (str[i])
		if (handler(str, &i, &lex, &token) < 0)
			return (NULL);
	return (token);
}
