/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:50:50 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/11 17:53:17 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	how_many_quotes(t_token *root, t_utils *data)
{
	char	quote;
	size_t	length;

	if (root->id == ARG)
	{
		length = ft_strlen(root->str);
		quote = root->str[0];
		if (root->str[length - 1] == quote)
			return (1);
	}
	if (data->simple_quotes % 2 != 0 || data->double_quotes % 2 != 0)
		return (show_error_fd("Quotes open/close error", 0, data, 0));
	return (1);
}
