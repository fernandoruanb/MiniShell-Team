/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-handle_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:41:29 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/14 10:38:46 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	handle_or(char *str, t_token **token, t_lex *lex)
// {
// 	(*token) = token_add((*token),
// 			token_create(str, 2, lex->index++, OPERATOR_OR), NULL);
// 	lex->id = CMD;
// 	return (2);
// }

int	handle_pipe(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '|')
		i++;
	if (i > 1)
		return (error_message("Error:\n\nToo many pipes.", -1, token));
	(*token) = token_add((*token),
			token_create(str, i, lex->index++, PIPE), NULL);
	lex->id = CMD;
	return (i);
}
