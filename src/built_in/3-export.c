/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:25:19 by jonas             #+#    #+#             */
/*   Updated: 2025/02/16 13:26:45 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	namevalidation(char *input)
{
	int	i;

	if (!input || !valid_name(input[0], 1))
		return (0);
	i = 0;
	while (input[i] && input[i] != '=')
		if (!valid_name(input[i++], 0))
			return (0);
	return (i);
}

static char	*get_var(char *input)
{
	char	*var;
	int		i;

	i = 0;
	while (input[i])
		if (input[i++] == ' ' && !is_quote(input[0]))
			break ;
	var = calloc(i + 1, 1);
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

static int	my_free_my_life(void *s1, void *s2, void *s3, int __return__)
{
	free(s1);
	free(s2);
	free(s3);
	return (__return__);
}

static t_export	*export_last(t_export **var)
{
	t_export	*temp;

	temp = *var;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

int	ft_export(char *input, t_export **var)
{
	int 		len;
	t_export	*new;
	t_export	*temp;

    if (!input)
        return (1);
    len = namevalidation(input);
    if (!len)
        return (1);
    new = calloc(sizeof(t_export), 1);
    if (!new)
        return (1);
    new->name = ft_strndup(input, len);
    new->value = get_var(&input[len + 1]);
    if (!new->name || !new->value)
        return (my_free_my_life(new->name, new->value, new, 1));
	if (!(*var))
		*var = new;
	else
	{
		temp = export_last(var);
		temp->next = new;
		new->prev = temp;
	}
    return (0);
}
