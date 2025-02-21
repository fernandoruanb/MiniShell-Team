/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-remove_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:25:35 by jonas             #+#    #+#             */
/*   Updated: 2025/02/21 12:44:30 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nonquoteslen(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		len += !is_quote(str[i]);
		i += 1 + (str[i] == '\\');
	}
	return (len);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new;

	if (!str)
		return (NULL);
	new = ft_calloc (get_nonquoteslen(str) + 1, 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!is_quote(str[i]))
			new[j++] = str[i];
		i += 1 + (str[i] == '\\');
	}
	free(str);
	return (new);
}
