/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-handle_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:44:28 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/14 12:50:38 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(unsigned char c)
{
	return (c == '\'' || c == '\"');
}

int	quote_close(char *str, int k)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i++])
		if (is_quote(str[i]) && i != k)
			return (i);
	return (0);
}

int	handle_bracket(char *str, t_token **token, t_lex *lex)
{
	if (str[0] == '(' || str[0] == ')')
		error_message("ERROR:\n\n '()' detected.\n", -1, token);
	lex->id = CMD;
	return (-1);
}

int	handle_fd(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '<' || str[i] == '>')
		return (ft_atoi_but_better(str) >= 0);
	return (0);
}
