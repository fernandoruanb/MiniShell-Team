/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-converttosplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:18:00 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/17 15:44:42 by jopereir         ###   ########.fr       */
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
		cnt += 1 * temp->id != ARG;
		temp = temp->next;
	}
	return (cnt);
}

void	print_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		printf("%s ", split[i++]);
	printf("\n");
}

void	print_array(char ***array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		print_split(array[i++]);
}

void	*clean_array(char ***array)
{
	int	i;

	if (!array)
		return (NULL);
	i = -1;
	while (array[++i])
		clear_split(array[i]);
	return (NULL);
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

	split = ft_calloc(cmdlen(token) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	split[i++] = ft_strdup((*token)->str);
	(*token) = (*token)->next; 
	while ((*token) && (*token)->id == ARG)
	{
		split[i++] = ft_strdup((*token)->str);
		(*token) = (*token)->next;
	}
	return (split);
}

char	**make_op(t_token **token)
{
	char	**split;

	split = ft_calloc(2, sizeof(char *));
	if (!split)
		return (NULL);
	split[0] = ft_strdup((*token)->str);
	(*token) = (*token)->next;
	return (split);
}

char	***converttokentosplit(t_token **token)
{
	char	***array;
	int		i;
	t_token	*temp;

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
