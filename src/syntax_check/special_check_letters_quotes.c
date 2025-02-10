/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_check_letters_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:45:02 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/10 09:02:11 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	special_check_letters_quotes(t_token *root, t_utils *data)
{
	int	letters;
	int	index;

	letters = 0;
	index = 0;
	while (root->str[index] != '\0')
	{
		if (ft_isalpha_special(root->str[index]))
			letters++;
		else if ((root->str[index] == '\'' || root->str[index] == '\"'))
		{
			if (root->str[index] == '\'')
				data->simple_quotes++;
			else
				data->double_quotes++;
		}
		index++;
	}
	return (how_many_quotes(root, data, letters));
}
