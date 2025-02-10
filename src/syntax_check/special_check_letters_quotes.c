/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_check_letters_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:48:46 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/10 12:50:22 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	special_check_quotes(t_token *root, t_utils *data)
{
	int	index;

	index = 0;
	while (root->str[index] != '\0')
	{
		if ((root->str[index] == '\'' || root->str[index] == '\"'))
		{
			if (root->str[index] == '\'')
				data->simple_quotes++;
			else
				data->double_quotes++;
		}
		index++;
	}
	return (how_many_quotes(data));
}
