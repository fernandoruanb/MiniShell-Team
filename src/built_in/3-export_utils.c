/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:53:03 by jonas             #+#    #+#             */
/*   Updated: 2025/03/05 12:10:09 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_clean(t_export **var)
{
	while (*var)
		ft_unset(var, NULL, (*var)->name);
}

void	export_init(char **envp, t_export **var)
{
	int	i;

	ft_quicksort(envp, 0, splitlen(envp) - 1);
	i = -1;
	while (envp[++i])
		ft_export(envp[i], var);
}
