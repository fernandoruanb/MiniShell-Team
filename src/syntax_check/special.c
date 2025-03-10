/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:46:04 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/10 13:25:39 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	special(t_token *root, t_utils *data)
{
	if (data->new_str)
	{
		free(data->new_str);
		data->new_str = NULL;
	}
	if (!data->paths)
		return (1);
	data->simple_quotes = 0;
	data->double_quotes = 0;
	if (!special_check_quotes(root, data))
		return (0);
	if (!check_quotes(root))
		return (0);
	if (!get_check_command(root, data))
		return (0);
	return (1);
}
