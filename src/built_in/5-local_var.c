/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6-local_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:47:54 by jonas             #+#    #+#             */
/*   Updated: 2025/02/16 16:30:02 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static t_localvar	*local_last(t_localvar **var)
{
	t_localvar	*temp;

	temp = *var;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

int	ft_localvar(char *input, t_localvar **var)
{
	int 		len;
	t_localvar	*new;
	t_localvar	*temp;

    if (!input)
        return (1);
    len = namevalidation(input);
    if (!len)
        return (1);
    new = ft_calloc(sizeof(t_export), 1);
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
		temp = local_last(var);
		temp->next = new;
		new->prev = temp;
	}
    return (0);
}

void	locals_print(t_localvar **var)
{
	t_localvar	*temp;

	temp = *var;
	while(temp)
	{
		printf("local: %s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

void	clean_locals(t_localvar	*var)
{
	if (!var)
		return ;
	if (var->next)
		clean_locals(var->next);
	free(var->name);
	free(var->value);
	free(var);
}
