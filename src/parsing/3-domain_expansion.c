/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-domain_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:24:54 by jonas             #+#    #+#             */
/*   Updated: 2025/03/14 14:46:57 by jonas            ###   ########.fr       */
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
	printf("status antes do wEXIT: %d\n", data->prompt->exit_status);
	if (data->prompt->exit_status > 255)
		data->prompt->exit_status = WEXITSTATUS(data->prompt->exit_status);
	printf("status dps do wEXIT: %d\n", data->prompt->exit_status);
	return (ft_itoa(data->prompt->exit_status));
}

static char	*get_find(char *str, int n, int *i)
{
	char	*new;
	char	*temp;

	new = ft_strndup(str, n);
	if (find_quote(new))
	{
		(*i)--;
		temp = ft_strndup(new, int_ft_strlen(new) - 1);
		free(new);
		return (temp);
	}
	return (new);
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
	find = get_find(&str[*i - j + 1], j - 1, i);
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

static char	*complete_str(char *str, char *expand, char *prev, int *i)
{
	char	*tmp;
	char	*temp;

	if (!expand)
	{
		tmp = ft_strjoin(prev, &str[*i]);
		ft_double_free(str, prev);
		*i = 0;
		return (tmp);
	}
	tmp = ft_strjoin(prev, expand);
	ft_double_free(prev, expand);
	temp = ft_strjoin(tmp, &str[*i]);
	ft_double_free(tmp, str);
	*i = 0;
	return (temp);
}

char	*domain_expansion(char *str, t_data *data)
{
	int		i;
	char	*expand;
	char	*temp;

	if ((str[0] == '\'' && str[int_ft_strlen(str) - 1] == '\'')
		|| (str[1] == ' ' || str[1] == '\0'))
		return (str);
	i = -1;
	while (++i < int_ft_strlen(str))
	{
		if (str[i] == '$')
		{
			temp = ft_strndup(str, i);
			expand = search_content(str, data, &i);
			str = complete_str(str, expand, temp, &i);
		}
	}
	return (str);
}
