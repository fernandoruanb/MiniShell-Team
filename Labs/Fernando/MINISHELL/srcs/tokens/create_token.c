/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:20:25 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/30 13:20:30 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

t_tokens	create_token(t_data *data, char *value)
{
	t_tokens	*token;

	token = malloc(sizeof(t_tokens));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = define_type(value);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}
