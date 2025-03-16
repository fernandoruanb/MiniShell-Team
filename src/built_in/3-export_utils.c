/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:53:03 by jonas             #+#    #+#             */
/*   Updated: 2025/03/16 12:25:46 by jonas            ###   ########.fr       */
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

int	create_var(char *input, t_export **var, int len)
{
	t_export	*new;
	t_export	*temp;

	new = calloc(sizeof(t_export), 1);
	if (!new)
		return (1);
	new->name = ft_strndup(input, len);
	new->value = get_var(&input[len + 1]);
	if (!new->name || !new->value)
		return (my_free_my_life(new->name, new->value, new, 1));
	else if (!(*var))
		*var = new;
	else
	{
		temp = export_last(var);
		temp->next = new;
		new->prev = temp;
	}
	return (0);
}
