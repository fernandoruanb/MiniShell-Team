/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_variables_order.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:44:26 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/10 09:02:49 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_variables_order(t_token *root, int *index, int *flag)
{
	*index = 0;
	*flag = 0;
	if (root->str[0] == '\'' || root->str[0] == '\"')
		*index = 1;
}
