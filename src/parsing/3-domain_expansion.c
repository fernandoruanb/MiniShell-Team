/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-domain_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:24:54 by jonas             #+#    #+#             */
/*   Updated: 2025/02/21 12:50:28 by jopereir         ###   ########.fr       */
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

static char	*is_return(t_data *data, char *find)
{
	free(find);
	return (ft_strdup(ft_itoa(data->prompt->exit_status)));
}

static char	*search_content(char *str, t_data *data, int *i)
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
	find = ft_strndup(&str[*i - j + 1], j - 1);
	if (!ft_strcmp(find, "?"))
		return (is_return(data, find));
	temp = search_var(&data->export_vars, find);
	if (temp)
	{
		free(find);
		return (ft_strdup(temp->value));
	}
	temp2 = search_locals(&data->local_vars, find);
	free(find);
	if (temp2)
		return (ft_strdup(temp2->value));
	return (NULL);
}

static char	*complete_str(char *str, char *expand, t_data *data)
{
	char	*prev;
	char	*next;
	char	*new;
	int		i;

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
	if (find_var(prev))
		prev = domain_expansion(prev, data);
	return (prev);
}

char	*domain_expansion(char *str, t_data *data)
{
	int		i;
	char	*expand;
	char	*new;
	int		len;

	printf("str[0] %c\n", str[0]);
	if (str[0] == '\'')
		return (str);
	i = -1;
	len = ft_strlen(str);
	new = NULL;
	expand = NULL;
	while (++i < len)
		if (str[i] == '$')
		{
			expand = search_content(str, data, &i);
			if (expand)
				new = complete_str(str, expand, data);
		}
	free(str);
	return (new);
}
