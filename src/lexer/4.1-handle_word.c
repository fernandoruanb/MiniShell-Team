/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.1-handle_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:43:59 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/13 21:57:23 by jonas            ###   ########.fr       */
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
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	if (!env[i])
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

int	is_cmd(char *str, t_lex *lex)
{
	struct stat	st;

	if (stat(str, &st) == 0)
		if (S_ISDIR(st.st_mode))
			return (0);
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

static t_token	*last_token(t_token **token)
{
	t_token	*temp;

	if (!*token)
		return (NULL);
	temp = *token;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

void	get_label(t_lex *lex, t_token **token)
{
	t_token	*temp;

	temp = last_token(token);
	if ((lex->id != LIMITER)
		&& ((!ft_strncmp(lex->word, "xargs", 5)
				|| ((!temp || (temp->id != CMD && temp->id != ARG))
					&& is_cmd(lex->word, lex)))
			|| (ft_strncmp(lex->word, "./", 2) == 0
				&& ft_strcmp(lex->word, ".") != 0
				&& ft_strncmp(lex->word, "../", 3) != 0
				&& !ft_strcmp(lex->word, ".")) || lex->id == NONE))
		lex->id = CMD;
	else if (lex->id != FD && lex->id != LIMITER && lex->id != CMD)
		lex->id = ARG;
}
