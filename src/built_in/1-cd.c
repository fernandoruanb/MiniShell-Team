/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:24:06 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/06 18:50:27 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_cd(char *input)
// {
// 	char	*path;

// 	path = NULL;
// 	if (input[3] == '~')
// 		path = getenv("HOME");
// 	else if (input[3] == '-')
// 		path = getenv("OLDPWD");
// 	if (path == NULL)
// 	{
// 		if (chdir(input + 3) == -1)
// 			ft_printf("No such file or directory %s\n", input + 3);
// 	}
// 	else
// 		chdir(path);
// }

static char	*get_oldpwd(t_utils *data)
{
	char	*temp;
	char	*path;

	if (data->oldpwd == NULL)
		path = ".";
	else
	{
		path = data->oldpwd;
		temp = data->newpwd;
		data->newpwd = data->oldpwd;
		data->oldpwd = temp;
	}
	return (path);
}

static void	set_newpwd(t_utils *data, char *path)
{
	if (data->newpwd != NULL)
	{
		free(data->newpwd);
		data->newpwd = ft_strdup(path);
	}
	else
		data->newpwd = ft_strdup(path);
}

static void	set_oldpwd(t_utils *data)
{
	char	old[9000];

	if (getcwd(old, sizeof(old)) == NULL)
		return ;
	else
	{
		if (data->oldpwd != NULL)
		{
			free(data->oldpwd);
			data->oldpwd = ft_strdup(old);
		}
		else
			data->oldpwd = ft_strdup(old);
	}
}

static char	*get_home(t_utils *data, size_t length)
{
	char	*path;
	char	*temp;

	path = getenv("HOME");
	if (length > 4)
	{
		temp = ft_strjoin(path, data->line + 4);
		if (!temp)
			return (NULL);
		path = temp;
	}
	set_oldpwd(data);
	set_newpwd(data, path);
	return (path);
}

void	ft_cd(char *input)
{
	char	*path;
	t_data	data;
	size_t	length;

	path = NULL;
	if (input)
		length = ft_strlen(input);
	else
		length = 0;
	// if (input[3] == '~')
	// 	path = getenv("HOME");
	if (!input)
		path = get_home(&data.utils, length);
	else if (ft_strcmp(input, "-") == 0)
		path = get_oldpwd(&data.utils);
	if (path == NULL)
	{
		if (chdir(input) == -1)
			ft_printf("No such file or directory %s\n", input);
	}
	else
	{
		set_oldpwd(&data.utils);
		chdir(path);
		set_newpwd(&data.utils, path);
	}
}
