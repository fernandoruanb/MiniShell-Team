/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-converttosplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:18:00 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/17 12:50:15 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmdlen(t_token **token)
{
	t_token	*temp;
	int		cnt;

	cnt = 0;
	temp = *token;
	while (temp)
	{
		cnt += 1 * (temp->id == CMD || temp->id == ARG);
		temp = temp->next;
	}
	return (cnt);
}

static char	**get_elements(char **split, t_token **token)
{
	t_token	*temp;
	int		i;
	
	temp = *token;
	i = 0;
	while (temp && (temp->id == CMD || temp->id == ARG))
	{
		split[i] = ft_strdup(temp->str);
		if (!split)
			return (clear_split(split));
		i++;
		temp = temp->next;
	}
	return (split);
}

void	print_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		printf("%s ", split[i]);
	printf("\n");
}

char	**converttokentosplit(t_token **token)
{
	char	**split;

	split = ft_calloc(cmdlen(token) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	split = get_elements(split, token);
	print_split(split);
	return (split);
}
