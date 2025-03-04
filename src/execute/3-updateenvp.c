/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-updateenvp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:46:31 by jonas             #+#    #+#             */
/*   Updated: 2025/02/24 15:07:54 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	envplen(t_export **export)
{
	t_export	*temp;
	int			cnt;

	if (!*export)
		return (0);
	temp = *export;
	cnt = 0;
	while (temp)
	{
		cnt++;
		temp = temp->next;
	}
	return (cnt);
}

char	**updateenvp(t_export **export)
{
	char		**new_envp;
	t_export	*temp;
	int			i;
	char		*name;

	new_envp = NULL;
	new_envp = ft_calloc(envplen(export) + 1, sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	temp = *export;
	while (temp)
	{
		name = ft_strjoin(temp->name, "=");
		new_envp[i++] = ft_strjoin(name, temp->value);
		free(name);
		temp = temp->next;
	}
	return (new_envp);
}
