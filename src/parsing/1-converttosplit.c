/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-converttosplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:18:00 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/24 15:08:29 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	get_arraylen(t_token **token)
// {
// 	int		cnt;
// 	t_token	*temp;

// 	temp = (*token);
// 	cnt = 0;
// 	while (temp)
// 	{
// 		cnt += temp->id != ARG;
// 		temp = temp->next;
// 	}
// 	return (cnt);
// }

// static int	cmdlen(t_token **token)
// {
// 	int		cnt;
// 	t_token	*temp;

// 	cnt = 1;
// 	temp = (*token)->next;
// 	while (temp && (temp->id != CMD))
// 	{
// 		cnt += temp->id == ARG;
// 		temp = temp->next;
// 	}		
// 	return (cnt);
// }

// static char	**make_cmd(t_token **token)
// {
// 	char	**split;
// 	int		i;
// 	t_token	*fd;

// 	if (!(*token))
// 		return (NULL);
// 	split = ft_calloc(cmdlen(token) + 1, sizeof(char *));
// 	if (!split)
// 		return (NULL);
// 	i = 0;
// 	split[i++] = ft_strdup((*token)->str);
// 	(*token) = (*token)->next;
// 	fd = NULL;
// 	while ((*token) && (*token)->id != CMD && !is_operator((*token)->id))
// 	{
// 		if ((*token)->id == ARG)
// 			split[i++] = ft_strdup((*token)->str);
// 		else if ((*token)->id == FD || (*token)->id == LIMITER)
// 			fd = (*token)->previous;
// 		(*token) = (*token)->next;
// 	}
// 	if (fd)
// 		(*token) = fd;
// 	return (split);
// }

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
	temp = temp->next;
	while (temp && temp->id != CMD && temp->id != PIPE)
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
	printf("\n");
}
