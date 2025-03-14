/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-converttosplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:18:00 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/13 21:58:46 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmdlen(t_token **token)
{
	t_token	*temp;
	int		cnt;

	cnt = 0;
	temp = *token;
	if (temp->id == CMD)
	{
		cnt++;
		temp = temp->next;
	}
	while (temp && temp->id != CMD && temp->id != PIPE)
	{
		if (temp->id == ARG)
			cnt++;
		temp = temp->next;
	}
	return (cnt);
}

char	**convert_to_cmd(t_token **token)
{
	char	**split;
	int		i;
	t_token	*temp;
	int		len;

	if (!*token)
		return (NULL);
	temp = *token;
	len = cmdlen(token);
	split = NULL;
	split = ft_calloc(len + 2, sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	split[i++] = ft_strdup(temp->str);
	len = temp->id == CMD;
	temp = temp->next;
	while (temp && len && temp->id != CMD)
	{
		if (temp->id == ARG)
			split[i++] = ft_strdup(temp->str);
		temp = temp->next;
	}
	split[i] = NULL;
	return (split);
}

void	print_split(char **split)
{
	int	i;

	if (!split || !*split)
		return ;
	i = 0;
	while (split[i])
		printf("%s\n", split[i++]);
}
