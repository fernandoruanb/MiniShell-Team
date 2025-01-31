/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:48:06 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/31 17:08:24 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#pragma region Utils

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*dup;

	if (!str)
		return (NULL);
	dup = calloc(n + 1, 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

#pragma endregion

#pragma region Token

typedef enum e_id
{
	PIPE,
	CMD,
	ARG,
	BRACKET,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	APPEND,
	OPERATOR_OR,
	OPERATOR_AND
}	t_id;

typedef struct s_token
{
	char			*str;
	t_id			id;
	int				index;

	struct s_token	*next;
}	t_token;

t_token	*token_create(char *str,int n, int index,  t_id id)
{
	t_token	*new;

	new = calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strndup(str, n);
	new->id = id;
	new->next = NULL;
	new->index = index;
	return (new);
}

t_token	*token_add(t_token *root, t_token *new)
{
	if (!root)
		return (new);
	root->next = token_add(root->next, new);
	return (root);
}

void	token_clean(t_token *token)
{
	if (!token)
		return ;
	token_clean(token->next);
	free(token->str);
	free(token);
}

int	token_len(t_token *token)
{
	if (!token)
		return (0);
	return (1 + token_len(token->next));
}

void	token_print(t_token *token)
{
	if (!token)
		return ;
	if (token->id == CMD)
		printf("Token %d: %s Tipo: CMD\n", token->index, token->str);
	else if (token->id == PIPE)
		printf("Token %d: %s Tipo: PIPE\n", token->index, token->str);
	else if (token->id == REDIRECT_IN)
		printf("Token %d: %s Tipo: REDIRECT_IN\n", token->index, token->str);
	else if (token->id == REDIRECT_OUT)
		printf("Token %d: %s Tipo: REDIRECT_OUT\n", token->index, token->str);
	else if (token->id == ARG)
		printf("Token %d: %s Tipo: ARG\n", token->index, token->str);
	else if (token->id == HEREDOC)
		printf("Token %d: %s Tipo: HEREDOC\n", token->index, token->str);
	else if (token->id == APPEND)
		printf("Token %d: %s Tipo: APPEND\n", token->index, token->str);
	token_print(token->next);
}

#pragma endregion

#pragma region Check

int	is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '.' || c == '-'));
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_pipe(char c)
{
	return (c == '|');
}

int	is_great(char c)
{
	return (c == '>');
}

int	is_less(char c)
{
	return (c == '<');
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&');
}
#pragma endregion

#pragma region Handles 

int	handle_word(char *str, t_token **token, int index)
{
	int	i;

	i = -1;
	while (str[++i])
		if (is_operator(str[i]))
			break ;
	(*token) = token_add((*token), token_create(str, i, index, CMD));
	return (i);
}

int	handle_quote(char *str, t_token **token, int index)
{
	char	quote;
	int		i;
	
	i = 0;
	quote = str[i++];
	while (str[i])
	{
		if (str[i++] == quote)
		{
			(*token) = token_add((*token), token_create(str, i, index, CMD));
			return (i);
		}
	}
	token_clean(*token);
	return (-1);
}

int	handle_or(char *str, t_token **token, int index)
{
	(*token) = token_add((*token), token_create(str, 2, index, OPERATOR_OR));
	return (2);
}

int	handle_pipe(char *str, t_token **token, int index)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!is_pipe(str[i]))
			break ;
	if (i == 2)
		return (handle_or(str, token, index));
	if (i > 2)
	{
		token_clean(*token);
		return (-1);
	}
	else
		(*token) = token_add((*token), token_create(str, i, index, PIPE));
	return (i);
}

int	handle_append(char *str, t_token **token, int index)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!is_great(str[i]))
			break ;
	(*token) = token_add((*token), token_create(str, i, index, APPEND));
	return (i);
}

int	handle_great(char *str, t_token **token, int index)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!is_great(str[i]))
			break ;
	if (i == 2)
		return (handle_append(str, token, index));
	if (i > 2)
	{
		token_clean(*token);
		return (-1);
	}
	else
		(*token) = token_add((*token), token_create(str, i, index, REDIRECT_OUT));
	return (i);
}

int	handle_heredoc(char *str, t_token **token, int index)
{
	(*token) = token_add((*token), token_create(str, 2, index, HEREDOC));
	return (2);
}

int	handle_less(char *str, t_token **token, int index)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!is_less(str[i]))
			break ;
	if (i == 2)
		return (handle_heredoc(str, token, index));
	if (i > 2)
	{
		token_clean(*token);
		return (-1);
	}
	else
		(*token) = token_add((*token), token_create(str, i, index, REDIRECT_IN));
	return (i);
}

#pragma endregion

#pragma region lexer

static int	handler(char *str, int *i, int *index, t_token **token)
{
	int	__return__;

	__return__ = 0;
	if (is_alpha(str[*i]))
		 __return__ = handle_word(&str[*i], token, (*index)++);
	if (is_quote(str[*i]))
		__return__ = handle_quote(&str[*i], token, (*index)++);
	if (is_pipe(str[*i]))
		__return__ = handle_pipe(&str[*i], token, (*index)++);
	if (is_great(str[*i]))
		__return__ = handle_great(&str[*i], token, (*index)++);
	if (is_less(str[*i]))
		__return__ = handle_less(&str[*i], token, (*index)++);
	if (__return__ != 0)
		*i += __return__;
	else
		(*i)++;
	return (__return__);
}

t_token	*lexer(char *str)
{
	int		i;
	t_token	*token;
	int		index;

	i = 0;
	index = 0;
	token = NULL;
	while (str[i])
		if (handler(str, &i, &index, &token) < 0)
			return (NULL);
	return (token);
}

#pragma endregion

int	main(int argc, char **argv)
{
	t_token	*token;

	if (argc != 2)
		return (1);
	token = lexer(argv[1]);
	token_print(token);
	printf("Tamanho do token: %d\n", token_len(token));
	token_clean(token);
	return (0);
}
