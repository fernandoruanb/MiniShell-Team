/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:21:51 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/17 18:13:46 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_file_descriptor(t_token *root, char *file);

static int	get_substr(t_token *root)
{
	char	*substr;
	int		result;

	substr = ft_strdup(root->str + 2);
	if (!substr)
		return (0);
	result = check_file_descriptor(root, substr);
	free(substr);
	return (result);
}

static int	check_file_descriptor(t_token *root, char *file)
{
	t_token	*last;

	last = root;
	while (last->previous)
		last = last->previous;
	while (last->next)
	{
		if (last->previous != NULL && last->previous->id != REDIRECT_IN
			&& last->previous->id != HEREDOC && last->id == FD
			&& (ft_strcmp(last->str, file) == 0))
			return (1);
		last = last->next;
	}
	return (0);
}

static int	escaping_case(t_token *root, t_utils *data)
{
	int	index;

	index = 0;
	while (root->str[index] != '\0')
	{
		if (root->str[index] == '\\' && (root->str[index + 1] == '\''
				|| root->str[index + 1] == '\"'))
		{
			if (!pipes_case(root, data) && !start_case(root, data))
				return (1);
		}
		index++;
	}
	return (0);
}

static int	extra_cases_commands(t_token *root, t_utils *data)
{
	if (check_local_environment(root))
		return (1);
	if (pipes_case(root, data) || start_case(root, data))
		return (1);
	if ((root->id == CMD) && root->str[0] == '.' && root->str[1] == '/')
	{
		if (special_check_quotes(root, data)
			&& !check_is_directory(root, data) && get_substr(root))
		{
			data->status = 1;
			return (1);
		}
	}
	else if ((root->id == CMD) && (exist_command(root, data)
			|| check_absolute_path(root, data)
			|| is_insider_quotes(root, data) || special(root, data)))
	{
		data->status = 1;
		return (1);
	}
	return (0);
}

int	case_command(t_token *root, t_utils *data)
{
	if ((root->id == CMD && data->status > 1) && (exist_command(root, data)
			|| check_absolute_path(root, data)))
		return (decrement_status(data));
	else if (escaping_case(root, data))
		return (show_error_fd("Syntax Error: CMD Error", 0, data, 127));
	else if (case_builtins(root) || is_environment(root)
		|| is_insider_quotes(root, data) || special(root, data))
	{
		data->status = 1;
		return (1);
	}
	else if (root->previous != NULL
		&& ft_strcmp(root->previous->str, "xargs") == 0)
		return (1);
	else if (root->id == CMD && check_absolute_path(root, data))
		return (1);
	else if (root->id == CMD && root->next != NULL
		&& root->previous != NULL && root->previous->id == PIPE
		&& root->next->id == PIPE)
		return (1);
	else if (root->id == CMD && data->status == 1)
		return (show_error_fd("Syntax: CMD Error", 0, data, 1));
	else if (extra_cases_commands(root, data))
		return (1);
	return (show_error_fd("Syntax: CMD Error", 0, data, 127));
}
