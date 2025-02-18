/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:47 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/18 15:17:53 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	parser(t_token **token, t_data **data)
// {
// 	char	***array;

// 	array = (*data)->prompt->cmdset;
// 	array = converttokentosplit(token);
// 	if (!array || !*array)
// 		return (1);
// 	print_array(array);
// 	(void)clean_array(array);
// 	return (0);	
// }

static char	*remove_quotes(char *str)
{
	int		i;
	char	*new;

	if (!str)
		return (NULL);
	i = 1;
	while (str[i] && !is_quote(str[i]))
		i++;
	new = ft_strndup(&str[1], i - 1);
	if (!new)
		return (NULL);
	free(str);
	return (new);
}

static int	find_escape(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		if (str[i++] == '\\')
			return (1);
	return (0);
}

static char	*remove_escape(char *str)
{
	int		i;
	int		j;
	char	*new;

	if (!str)
		return (NULL);
	new = ft_calloc(ft_strlen(str) + 1, 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			i++;
			continue ;
		}
		new[j++] = str[i++];
	}
	free(str);
	return (new);
}

int	find_var(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		if (str[i++] == '$')
			return (1);
	return (0);
}


char	*domain_expantion(char *str, t_export **export, t_localvar **local)
{
	int		i;
	int		cnt;
	char	*find;
	char	*new;
	
	if (str[0] == '\'' || !str)
		return (str);
	i = -1;
	cnt = 0;
	new = NULL;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			while (str[i] && str[i] != ' ' && str[i] != '\"')
			{
				cnt++;
				i++;
			}
			find = ft_strndup(&str[i - cnt + 1], cnt);
			if (search_var(export, find))
				new = ft_strdup(search_var(export, find)->value);
			else if (search_locals(local, find))
				new = ft_strdup(search_locals(local, find)->value);
			free(find);
			if (new)
			{
				free(str);
				return (new);
			}
		}
	}
	return (str);
}

int	parser(t_token **token, t_data *data)
{
	t_token	*temp;

	temp = *token;
	if (find_var(temp->str))
		temp->str = domain_expantion(temp->str, &data->export_vars, &data->local_vars);
	if (is_quote(temp->str[0]))
		temp->str = remove_quotes(temp->str);
	if (find_escape(temp->str))
		temp->str = remove_escape(temp->str);
	return (0);
}
