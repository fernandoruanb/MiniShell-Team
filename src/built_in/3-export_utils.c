/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:53:03 by jonas             #+#    #+#             */
/*   Updated: 2025/03/14 15:07:34 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_clean(t_export **var)
{
	while (*var)
		ft_unset(var, NULL, (*var)->name);
}

static char	**clone_env(char **env)
{
	char	**new;
	int		i;

	new = ft_calloc(splitlen(env) + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	return (new);
}

void	export_init(char **envp, t_export **var)
{
	char	**temp;

	temp = clone_env(envp);
	ft_quicksort(temp, 0, splitlen(temp) - 1);
	ft_export(temp, var);
	clear_split(temp);
}
