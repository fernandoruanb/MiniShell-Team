/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.1-make_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:53:33 by jonas             #+#    #+#             */
/*   Updated: 2025/03/16 11:55:22 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_exit_code(t_data *data)
{
	int	status;

	status = data->prompt->exit_status;
	if (status > 255)
		status = WEXITSTATUS(status);
	return (ft_itoa(status));
}

static char	*get_name(char *str)
{
	char	*name;
	char	*temp;
	int		j;
	int		start;

	start = 0;
	while (str[start] && (str[start] == '$' || str[start] == '\"'))
		start++;
	j = start;
	while (str[j] && str[j] != '\"' && str[j] != ' ' && str[j] != '$')
		j++;
	name = ft_strndup(&str[start], j);
	if (is_quote(name[j - 1]) || name[j - 1] == '$' || name[j - 1] == ' ')
	{
		temp = ft_strndup(name, --j);
		free(name);
		name = temp;
	}
	return (name);
}

static char	*search_content(char *str, int i, t_data *data)
{
	char		*name;
	t_export	*export;
	t_localvar	*local;

	name = get_name(&str[i]);
	export = search_var(&data->export_vars, name);
	if (export)
	{
		free(name);
		return (ft_strdup(export->value));
	}
	local = search_locals(&data->local_vars, name);
	free(name);
	if (local)
		return (ft_strdup(local->value));
	return (NULL);
}

char	*make_expansion(char *str, t_data *data, int i)
{
	if (!str)
		return (NULL);
	(void)data;
	if (!ft_strncmp(&str[i], "$?", 2))
		return (get_exit_code(data));
	return (search_content(str, i, data));
}
