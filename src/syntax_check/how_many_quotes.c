/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:45:28 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/10 09:02:25 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	how_many_quotes(t_token *root, t_utils *data, int letters)
{
	if (root->str[0] == '/')
		letters--;
	if (root->str[0] == '\'' || root->str[0] == '\"')
		letters++;
	if (data->simple_quotes % 2 != 0 || data->double_quotes % 2 != 0)
		return (0);
	if (letters == (data->simple_quotes + data->double_quotes))
		return (1);
	else
		return (show_error_fd("letters != quotes", 0, data, 0));
}
