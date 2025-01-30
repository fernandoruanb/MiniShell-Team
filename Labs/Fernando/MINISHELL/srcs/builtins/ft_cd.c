/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:53:36 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/30 11:33:50 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static char	*get_oldpwd(t_data *data)
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

static void	set_newpwd(t_data *data, char *path)
{
	if (data->newpwd != NULL)
	{
		free(data->newpwd);
		data->newpwd = ft_strdup(path);
	}
	else
		data->newpwd = ft_strdup(path);
}

static void	set_oldpwd(t_data *data)
{
	char	old[4096];

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

static char	*get_home(t_data *data, size_t length)
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

void	ft_cd(t_data *data)
{
	char	*path;
	size_t	length;

	length = ft_strlen(data->line);
	if ((ft_strncmp(data->line, "cd", 2) == 0) && is_only_spaces(data))
		path = get_home(data, length);
	else if (ft_strncmp(data->line, "cd ~", 4) == 0)
		path = get_home(data, length);
	else if (ft_strncmp(data->line, "cd -", 4) == 0)
		path = get_oldpwd(data);
	else
	{
		set_oldpwd(data);
		path = data->line + 3;
		set_newpwd(data, path);
	}
	data->status = chdir(path);
	if (data->status != 0)
		ft_printf("No such file or directory: %s\n", path);
}
