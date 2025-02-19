/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:47 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/19 13:56:36 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_var(char *str)
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
