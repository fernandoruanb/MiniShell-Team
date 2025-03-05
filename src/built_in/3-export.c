/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:25:19 by jonas             #+#    #+#             */
/*   Updated: 2025/03/05 12:10:38 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	namevalidation(char *input, t_export **var)
{
	int			i;
	char		*name;
	t_export	*temp;

	if (!input || !valid_name(input[0], 1))
		return (0);
	i = 0;
	while (input[i] && input[i] != '=')
		if (!valid_name(input[i++], 0))
			return (0);
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
		if (input[i++] == ' ' && !is_quote(input[0]))
			break ;
	var = ft_calloc(i + 1, 1);
	if (!var)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' && !is_quote(input[0]))
			break ;
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

	temp = *var;
	while(temp)
	{
		printf("declare -x %s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	return (0);
}

int	ft_export(char *input, t_export **var)
{
	int 		len;
	t_export	*new;
	t_export	*temp;

    if (!input)
        return (export_print(var));
    len = namevalidation(input, var);
    if (!len)
        return (1);
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
