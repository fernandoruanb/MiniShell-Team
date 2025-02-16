/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:50:50 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/15 20:28:03 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_final_quotes(t_token *root)
{
	int		index;
	char	quote;

	index = 0;
	while (root->str[index] != '\0')
	{
		if (root->str[index] == '\'' || root->str[index] == '\"')
		{
			quote = root->str[index];
			index++;
			while (root->str[index] != '\0' && root->str[index] != quote)
				index++;
			if (root->str[index] == '\0')
				return (0);
		}
		index++;
	}
	return (1);
}

int	how_many_quotes(t_token *root, t_utils *data)
{
	if (root->id == ARG && check_final_quotes(root))
		return (1);
	if (data->simple_quotes % 2 != 0 || data->double_quotes % 2 != 0)
		return (show_error_fd("Syntax: QUOTES Error", 0, data, 0));
	else
		return (1);
	return (0);
}
