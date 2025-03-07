/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:47 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/07 12:53:39 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// static int	find_escape(char *str)
// {
// 	int	i;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	while (str[i])
// 		if (str[i++] == '\\')
// 			return (1);
// 	return (0);
// }

int	find_quote(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			return (1);
		i += 1 + (str[i] == '\\');
	}		
	return (0);
}

static int	find_tilde(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '~' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			if (i == 0 || (i > 0 && str[i - 1] == ' '))
				return (1);
	return (0);
}

int	count_var(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
		if (str[i++] == '$')
			cnt++;
	return (cnt);
}

int	parser(t_token **token, t_data *data)
{
	t_token	*temp;

	temp = *token;
	if (find_tilde(temp->str))
		temp->str = expand_tilde(temp->str);
	if (find_var(temp->str))
		temp->str = domain_expansion(temp->str, data);
	if (find_quote(temp->str))
		temp->str = remove_quotes(temp->str);
	return (0);
}
