/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:47:09 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/10 13:14:17 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quotes(t_token *root)
{
	int		index;
	char	quote;
	int		flag;

	index = 0;
	flag = 0;
	while (root->str[index] != '\0')
	{
		if ((flag == 1) && (root->str[index] == '\''
				|| root->str[index] == '\"'))
		{
			if (quote != root->str[index])
				return (0);
			flag = 0;
		}
		else if (root->str[index] == '\'' || root->str[index] == '\"')
		{
			flag = 1;
			quote = root->str[index];
		}
		index++;
	}
	return (1);
}
