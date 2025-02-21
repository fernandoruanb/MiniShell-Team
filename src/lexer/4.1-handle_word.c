/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.1-handle_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:43:59 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/21 13:38:47 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_me(char **split, char *s1, char *s2, int exit)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	free(s1);
	free(s2);
	return (exit);
}

static	int	find_my_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*path;
	char	*temp;

	if (!cmd)
		return (0);
	i = 0;
	while (!ft_strnstr(env[i], "PATH=", 5))
		i++;
	if (!env)
		return (0);
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		if (access(path, X_OK) == 0)
			return (free_me(paths, path, temp, 1));
		free(path);
		free(temp);
		i++;
	}
	return (free_me(paths, NULL, NULL, 0));
}

static int	is_cmd(char *str, t_lex *lex)
{
	struct stat	st;

	if (stat(str, &st) == 0)
        if (S_ISDIR(st.st_mode))
            return 0;
	if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "env") == 0 || ft_strcmp(str, "echo") == 0
		|| ft_strcmp(str, "exit") == 0 || ft_strcmp(str, "clear") == 0)
		return (1);
	if (access(str, F_OK | X_OK) == 0)
		return (1);
	if (find_my_path(str, lex->envp))
		return (1);
	return (0);
}

void	get_label(t_lex *lex)
{
	if (lex->id != LIMITER && ((is_cmd(lex->word, lex) && lex->id != FD) || lex->id == NONE || ft_strncmp(lex->word, "./", 2) == 0)
		&& ft_strcmp(lex->word, ".") != 0 && ft_strncmp(lex->word, "../", 3) != 0)
		lex->id = CMD;
	else if (lex->id != FD && lex->id != LIMITER && lex->id != CMD)
		lex->id = ARG;
}