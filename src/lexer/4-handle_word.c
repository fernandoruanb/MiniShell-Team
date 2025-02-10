/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-handle_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:43:59 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/10 11:56:55 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(unsigned char c, int flag)
{
	if (flag == 1)
		return ((c != ' ' && c != '&' && c != '|' && c != '(' && c != ')'
			&& c != '<' && c != '>') || is_quote(c));
	if (flag == 2)
		return ((c != '&' && c != '|' && c != '(' && c != ')'
			&& c != '<' && c != '>') || is_quote(c));
	return ((c != ' ' && c != '&' && c != '|' && c != '(' && c != ')'
			&& c != '<' && c != '>') && !(is_quote(c)));
}

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

int	handle_word(char *str, t_token **token, t_lex *lex)
{
	int	i;
	int	flag;

	i = 0;
	if ((is_cmd(lex->word, lex) && lex->id != FD) || lex->id == NONE)
		lex->id = CMD;
	else if (lex->id != FD && lex->id != LIMITER && lex->id != CMD)
		lex->id = ARG;
	flag = 1;
	if (lex->id != CMD && (is_quote(str[i]) || str[i] == '\\'))
		flag = 2;
	while (str[i] && is_word(str[i], flag))
		i++;
	(*token) = token_add((*token),
			token_create(str, i, lex->index++, lex->id), NULL);
	if (((lex->id == CMD || lex->id == FD || lex->id == LIMITER) && ft_strncmp(str, "xargs", 5) != 0))
		lex->id = ARG;
	else if (lex->id == FD)
		lex->id = CMD;
	return (i);
}
