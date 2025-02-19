/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-domain_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:24:54 by jonas             #+#    #+#             */
/*   Updated: 2025/02/19 16:07:37 by jonas            ###   ########.fr       */
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

static char	*search_content(char *str, t_export **export, t_localvar **local, int i)
{
	char		*find;
	int			j;
	t_export	*temp;
	t_localvar	*temp2;

	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\"' && str[i] != '\\')
	{
		i++;
		j++;
	}
	find = ft_strndup(&str[i - j + 1], j - 1);
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

static char	*complete_str(char *str, char *expand)
{
	int		i;
	char	*prev;
	char	*next;
	char	*new;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	prev = ft_strndup(str, i);
	if (!prev)
		return (NULL);
	while (str[i] && str[i] != ' ' && str[i] != '\"' && str[i] != '\\')
		i++;
	new = ft_strjoin(prev, expand);
	(void)ft_double_free(prev, expand);
	if (!new)
		return (NULL);
	next = ft_strdup(&str[i]);
	prev = ft_strjoin(new, next);
	(void)ft_double_free(next, new);
	return (prev);
}

char	*domain_expantion(char *str, t_export **export, t_localvar **local)
{
	int		i;
	char	*expand;
	char	*new;

	printf("domain expansion!!\n");
	if (str[0] == '\'')
		return (str);
	i = -1;
	new = NULL;
	expand = NULL;
	while (str[++i])
		if (str[i] == '$')
		{
			expand = search_content(str, export, local, i);
			if (expand)
				new = complete_str(str, expand);
		}
	free(str);
	return (new);
}
