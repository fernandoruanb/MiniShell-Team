/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-domain_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:24:54 by jonas             #+#    #+#             */
/*   Updated: 2025/03/16 11:47:18 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_after(char *str, int i)
{
	i++;
	while (str[i] && str[i] != '$' && str[i] != '\"' && str[i] != ' ')
		i++;
	return (ft_strdup(&str[i]));
}

static char	*put_together(char *prev, char *expand, char *after)
{
	char	*temp;
	char	*temp2;

	temp = ft_strjoin(prev, expand);
	if (!temp)
		return (NULL);
	ft_double_free(prev, expand);
	temp2 = ft_strjoin(temp, after);
	ft_double_free(temp, after);
	return (temp2);
}

static char	*make_replacement(char *str, char *expand, int *i)
{
	char	*exp;
	char	*prev;
	char	*after;

	if (!expand)
		return (str);
	prev = ft_strndup(str, *i);
	after = get_after(str, *i);
	exp = put_together(prev, expand, after);
	if (!exp)
		return (str);
	*i = 0;
	free(str);
	return (exp);
}

char	*domain_expansion(char *str, t_data *data)
{
	char	*expand;
	int		i;

	if ((!str || !data) || str[0] == '\'')
		return (str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			expand = make_expansion(str, data, i);
			printf("expand: %s\n", expand);
			str = make_replacement(str, expand, &i);
		}
	}
	return (str);
}
