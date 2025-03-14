/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:09:31 by jonas             #+#    #+#             */
/*   Updated: 2025/03/14 12:08:56 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

t_token		*token_create(char *str, int n, int index, t_id id);
t_token		*token_add(t_token *token, t_token *new, t_token *prev);
void		token_clean(t_token *token);
/*
	temporaria, apagar antes de mandar
*/
void		token_print(t_token *token);

#endif
