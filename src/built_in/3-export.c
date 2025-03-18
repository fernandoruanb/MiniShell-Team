/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:25:19 by jonas             #+#    #+#             */
/*   Updated: 2025/03/18 09:30:06 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	namevalidation(char *input, t_export **var)
{
	int			i;
	char		*name;
	t_export	*temp;

	if (!input || !valid_name(input[0], 1))
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (0);
	}
	i = 0;
	while (input[i] && input[i] != '=')
		if (!valid_name(input[i++], 0))
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			return (0);
		}
	name = ft_strndup(input, i);
	temp = search_var(var, name);
	if (temp)
		ft_unset(var, NULL, name);
	free(name);
	return (i);
}

char	*get_var(char *input)
{
	char	*var;
	int		i;

	i = 0;
	while (input[i])
		i++;
	var = ft_calloc(i + 1, 1);
	if (!var)
		return (NULL);
	i = 0;
	while (input[i])
	{
		var[i] = input[i];
		i++;
	}
	return (var);
}

t_export	*export_last(t_export **var)
{
	t_export	*temp;

	temp = *var;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

int	export_print(t_export **var)
{
	t_export	*temp;

	if (!*var)
		return (0);
	temp = *var;
	while (temp)
	{
		printf("declare -x %s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	return (0);
}

int	ft_export(char **input, t_export **var)
{
	int			len;
	int			i;

	if (!input || !input[0])
		return (export_print(var));
	i = -1;
	while (input[++i])
	{
		len = namevalidation(input[i], var);
		if (!len)
			return (1);
		create_var(input[i], var, len);
	}
	return (0);
}
