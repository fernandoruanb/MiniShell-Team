/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_check_letters_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:48:46 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/11 13:43:32 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	special_check_quotes(t_token *root, t_utils *data)
{
	int	index;

	data->simple_quotes = 0;
	data->double_quotes = 0;
	index = 0;
	while (root->str[index] != '\0')
	{
		if ((root->str[index] == '\'' || root->str[index] == '\"'))
		{
			if (root->str[index] == '\'' && root->str[index - 1] != '\\')
				data->simple_quotes++;
			else if (root->str[index - 1] != '\\')
				data->double_quotes++;
		}
		index++;
	}
	return (how_many_quotes(data));
}
