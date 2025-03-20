/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-handle_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:41:29 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/20 16:36:18 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '|')
		i++;
	if (i > 1)
		return (error_message("Error:\n\nToo many pipes.\n", -1, token));
	(*token) = token_add((*token),
			token_create(str, i, lex->index++, PIPE), NULL);
	lex->id = CMD;
	return (i);
}

void	handle_empty(t_lex *lex, int *i, char *str)
{
	if (!ft_strcmp(lex->word, "$EMPTY"))
	{
		*i += 6;
		free (lex->word);
		lex->word = get_str(&str[*i]);
	}
}
