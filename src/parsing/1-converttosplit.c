/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-converttosplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:18:00 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/18 11:22:42 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_arraylen(t_token **token)
{
	int		cnt;
	t_token	*temp;

	temp = (*token);
	cnt = 0;
	while (temp)
	{
		cnt += temp->id != ARG;
		temp = temp->next;
	}
	return (cnt);
}

static int	cmdlen(t_token **token)
{
	int		cnt;
	t_token	*temp;

	cnt = 1;
	temp = (*token)->next;
	while (temp && (temp->id == ARG))
	{
		cnt++;
		temp = temp->next;
	}		
	return (cnt);
}

static char	**make_cmd(t_token **token)
{
	char	**split;
	int		i;
	t_token	*fd;

	if (!(*token))
		return (NULL);
	split = ft_calloc(cmdlen(token) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	split[i++] = ft_strdup((*token)->str);
	(*token) = (*token)->next;
	fd = NULL;
	while ((*token) && (*token)->id != CMD && !is_operator((*token)->id))
	{
		if ((*token)->id == ARG)
			split[i++] = ft_strdup((*token)->str);
		else if ((*token)->id == FD || (*token)->id == LIMITER)
			fd = (*token)->previous;
		(*token) = (*token)->next;
	}
	if (fd)
		(*token) = fd;
	return (split);
}

char	**make_op(t_token **token)
{
	char	**split;

	if (!(*token))
		return (NULL);
	split = ft_calloc(2, sizeof(char *));
	if (!split)
		return (NULL);
	split[0] = ft_strdup((*token)->str);
	(*token) = (*token)->next;
	if (*token && (*token)->id == ARG)
		while (*token && (*token)->id == ARG)
			*token = (*token)->next;
	return (split);
}

char	***converttokentosplit(t_token **token)
{
	char	***array;
	int		i;
	t_token	*temp;

	if (!(*token))
		return (NULL);
	printf("%d\n", get_arraylen(token));
	array = ft_calloc(get_arraylen(token) + 1, sizeof(char **));
	if (!array)
		return (NULL);
	temp = *token;
	i = 0;
	while (temp)
	{
		if (temp->id == CMD)
			array[i++] = make_cmd(&temp);
		else
			array[i++] = make_op(&temp);
	}
	array[i] = NULL;
	return (array);
}
