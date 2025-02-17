/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:25:26 by jonas             #+#    #+#             */
/*   Updated: 2025/02/17 12:05:24 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_init(char **envp, t_export **var)
{
	int	i;

	ft_quicksort(envp, 0, splitlen(envp) - 1);
	i = -1;
	while (envp[++i])
		ft_export(envp[i], var);
}

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

void	ft_unset(t_export **var, char *name)
{
	t_export	*temp;
/*
	unset deve liberar variaveis locais
*/
	if (!name)
		return ;
	temp = search_var(var, name);
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

void	export_clean(t_export **var)
{
	while (*var)
		ft_unset(var, (*var)->name);
}
