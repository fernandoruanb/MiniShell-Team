/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:25:26 by jonas             #+#    #+#             */
/*   Updated: 2025/03/04 12:34:21 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	the flag if to define if the first letter is valid

	set to 0 for all valid characters
*/
int	valid_name(char c, int flag)
{
	if (flag)
		return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) || c == '_');
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			|| c == '_'
			|| (c >= '0' && c <= '9'));
}

t_export	*search_var(t_export **var, char *name)
{
	t_export	*temp;

	temp = *var;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static void	clean_export(t_export **var, t_export *temp)
{
	if (!temp)
		return ;
	if (*var == temp)
		*var = temp->next;
	if (temp->prev)
		temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	free(temp->name);
	free(temp->value);
	free(temp);
}

static void	clean_local(t_localvar **local, t_localvar *temp)
{
	if (!temp)
		return ;
	if (*local == temp)
		*local = temp->next;
	if (temp->prev)
		temp->prev->next = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	free(temp->name);
	free(temp->value);
	free(temp);
}

void	ft_unset(t_export **var, t_localvar **local, char *name)
{
	t_export	*temp;
	t_localvar	*temp2;

	if (!name)
		return ;
	if (var)
	{
		temp = search_var(var, name);
		if (temp)
			return (clean_export(var, temp));
	}
	if (local)
	{
		temp2 = search_locals(local, name);
		if (temp2)
			return (clean_local(local, temp2));
	}
}
