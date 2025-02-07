/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_insider_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:24:11 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 12:24:34 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_insider_quotes(t_token *root, t_utils *data)
{
	size_t	length;

	if (data->new_str)
		free(data->new_str);
	if (!root)
		return (0);
	length = ft_strlen(root->str);
	if ((root->str[0] == '\'' && root->str[length - 1] == '\'')
		|| (root->str[0] == '\"' && root->str[length - 1] == '\"'))
	{
		data->new_str = ft_substr(root->str, 1, length - 2);
		if (!data->new_str)
			return (0);
		ft_printf("A new_str: %s\n", data->new_str);
		if (test_all_paths(data))
			return (1);
	}
	return (0);
}
