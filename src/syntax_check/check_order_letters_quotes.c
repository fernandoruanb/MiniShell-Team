/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_order_letters_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:43:17 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/12 16:56:27 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_order_letters_quotes(t_token *root, t_utils *data)
{
	int	index;
	int	flag;

	create_variables_order(root, &index, &flag);
	while (root->str[index] != '\0')
	{
		if (root->str[index - 1] == '/')
			flag = 0;
		if (ft_isalpha_special_2(root->str[index])
			&& flag == 0)
		{
			flag = 1;
			index++;
		}
		else if ((root->str[index] == '\'' || root->str[index] == '\"')
			&& flag == 1)
		{
			if (!case_quotes_syntax(root->str, index, &flag))
				return (0);
			index++;
		}
		else
			return (show_error_fd("Syntax: Invalid input", 0, data, 0));
	}
	return (1);
}
