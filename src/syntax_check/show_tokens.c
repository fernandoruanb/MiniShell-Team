/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:57:58 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/12 14:15:47 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	show_tokens(t_token *root)
{
	while (root)
	{
		printf("TOKEN %d\n", root->index);
		printf("Value: %s\nid: %s\n", root->str, get_token(root->id));
		if (root->next)
			printf("Next: %s\n", root->next->str);
		else
			printf("Next: NULL\n");
		if (root->previous)
			printf("Previous: %s\n", root->previous->str);
		else
			printf("Previous: NULL\n");
		root = root->next;
	}
}
