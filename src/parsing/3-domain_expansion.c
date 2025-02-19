/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-domain_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:24:54 by jonas             #+#    #+#             */
/*   Updated: 2025/02/19 13:48:11 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*domain_expantion(char *str, t_export **export, t_localvar **local)
// {
// 	int		i;
// 	int		cnt;
// 	char	*find;
// 	char	*new;
	
// 	if (str[0] == '\'' || !str)
// 		return (str);
// 	i = -1;
// 	cnt = 0;
// 	new = NULL;
// 	while (str[++i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			while (str[i] && str[i] != ' ' && str[i] != '\"')
// 			{
// 				cnt++;
// 				i++;
// 			}
// 			find = ft_strndup(&str[i - cnt + 1], cnt);
// 			if (search_var(export, find))
// 				new = ft_strdup(search_var(export, find)->value);
// 			else if (search_locals(local, find))
// 				new = ft_strdup(search_locals(local, find)->value);
// 			free(find);
// 			if (new)
// 			{
// 				free(str);
// 				return (new);
// 			}
// 		}
// 	}
// 	return (str);
// }

static char	*search_content(char *str, t_export **export, t_localvar **local, int *i)
{
	char		*find;
	int			j;
	t_export	*temp;
	t_localvar	*temp2;

	j = 0;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\"' && str[*i] != '\\')
	{
		(*i)++;
		j++;
	}
	find = ft_strndup(&str[*i - j + 1], j);
	if (!find)
		return (str);
	temp = search_var(export, find);
	if (temp)
	{
		free(find);
		return (ft_strdup(temp->value));
	}
	temp2 = search_locals(local, find);
	free(find);
	if (temp2)
		return (ft_strdup(temp2->value));
	return (str);
}

char	*domain_expantion(char *str, t_export **export, t_localvar **local)
{
	int		i;
	char	*new;

	if (str[0] == '\'')
		return (str);
	i = -1;
	new = NULL;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			new = search_content(str, export, local, &i);
			if (new)
			{
				free(str);
				return (new);
			}
		}
	}
	return (str);
}
