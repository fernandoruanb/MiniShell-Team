/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:53:03 by jonas             #+#    #+#             */
/*   Updated: 2025/03/10 12:09:11 by jopereir         ###   ########.fr       */
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
	int		i;
	char	**temp;

	temp = clone_env(envp);
	ft_quicksort(temp, 0, splitlen(temp) - 1);
	i = -1;
	while (temp[++i])
		ft_export(temp[i], var);
	clear_split(temp);
}
