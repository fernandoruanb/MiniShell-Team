/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:48:06 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/04 11:07:21 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#pragma region Utils

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while (s1[index] != '\0' && s2[index] != '\0' && index < n)
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	if (index < n)
		return ((unsigned char)s1[index] - (unsigned char)s2[index]);
	return (0);
}

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
    LIMITER,
    CMD,
    ARG,
    FD,
    BRACKET_O,
    BRACKET_C,
    REDIRECT_IN,
    REDIRECT_OUT,
    HEREDOC,
    APPEND,
    OPERATOR_OR,
    OPERATOR_AND
}    t_id;

typedef struct s_token
{
	char			*str;
	t_id			id;
	int				index;

	struct s_token	*next;
	struct s_token *previous;
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
	new->previous = NULL;
	new->index = index;
	return (new);
}

t_token	*token_add(t_token *root, t_token *new, t_token *prev)
{
	if (!root)
	{
		new->previous = prev;
		return (new);
	}
	root->next = token_add(root->next, new, root);
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
	else if (token->id == FD)
		printf("Token %d: %s Tipo: FD\n", token->index, token->str);
	else if (token->id == LIMITER)
		printf("Token %d: %s Tipo: LIMITER\n", token->index, token->str);
	else if (token->id == OPERATOR_AND)
		printf("Token %d: %s Tipo: OPERATOR_AND\n", token->index, token->str);
	else if (token->id == OPERATOR_OR)
		printf("Token %d: %s Tipo: OPERATOR_OR\n", token->index, token->str);
	else if (token->id == BRACKET_O)
		printf("Token %d: %s Tipo: BRACKET_O\n", token->index, token->str);
	else if (token->id == BRACKET_C)
		printf("Token %d: %s Tipo: BRACKET_C\n", token->index, token->str);
	token_print(token->next);
}

#pragma endregion

#pragma region Check

int	is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| c == '.' || c == '-' || c == '$' || (c >= '0' && c <= '9') || c == '/' || c == '_'
		|| c == '!' || c == '*' || c == '%' || c == '{' || c == '}');
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

#pragma endregion

typedef struct s_lex
{
	t_id	id;
	int		index;
}	t_lex;

#pragma region Handles 

int	diff_cmd(char *str)
{
	return (ft_strncmp(str, "xargs", 5) != 0);
}

int	handle_word(char *str, t_token **token, t_lex *lex)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!is_alpha(str[i]))
			break ;
	(*token) = token_add((*token), token_create(str, i, lex->index++, lex->id), NULL);
	if (lex->id == CMD && diff_cmd(str))
		lex->id = ARG;
	return (i);
}


//orginal
int	handle_quote(char *str, t_token **token, t_lex *lex)
{
	char	quote;
	int		i;
	
	i = 0;
	quote = str[i++];
	while (str[i])
	{
		if (str[i++] == quote)
		{
			(*token) = token_add((*token), token_create(str, i, lex->index++, lex->id), NULL);
			return (i);
		}
	}
	token_clean(*token);
	(*token) = NULL;
	return (-1);
}

//alterada
// int	handle_quote(char *str, t_token **token, t_lex *lex)
// {
// 	char	quote;
// 	int		i;
// 	int		cpy;
	
// 	i = 0;
// 	quote = str[i++];
// 	cpy = is_quote(str[i]);
// 	while (str[i++])
// 	{
// 		if (str[i] == quote)
// 		{
// 			(*token) = token_add((*token), token_create(&str[cpy], i - cpy, lex->index++, lex->id));
// 			return (i);
// 		}
// 	}
// 	token_clean(*token);
// 	(*token) = NULL;
// 	return (-1);
// }

int	handle_or(char *str, t_token **token, t_lex *lex)
{
	(*token) = token_add((*token), token_create(str, 2, lex->index++, OPERATOR_OR), NULL);
	lex->id = CMD;
	return (2);
}

int	handle_pipe(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!is_pipe(str[i]))
			break ;
	if (i == 2)
		return (handle_or(str, token, lex));
	if (i > 2)
	{
		token_clean(*token);
		return (-1);
	}
	else
		(*token) = token_add((*token), token_create(str, i, lex->index++, PIPE), NULL);
	lex->id = CMD;
	return (i);
}

int	handle_append(char *str, t_token **token, t_lex *lex)
{
	(*token) = token_add((*token), token_create(str, 2, lex->index++, APPEND), NULL);
	lex->id = FD;
	return (2);
}

int	handle_great(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!is_great(str[i]))
			break ;
	if (i == 2)
		return (handle_append(str, token, lex));
	if (i > 2)
	{
		token_clean(*token);
		return (-1);
	}
	else
		(*token) = token_add((*token), token_create(str, i, lex->index++, REDIRECT_OUT), NULL);
	lex->id = FD;
	return (i);
}

int	handle_heredoc(char *str, t_token **token, t_lex *lex)
{
	(*token) = token_add((*token), token_create(str, 2, lex->index++, HEREDOC), NULL);
	lex->id = LIMITER;
	return (2);
}

int	handle_less(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!is_less(str[i]))
			break ;
	if (i == 2)
		return (handle_heredoc(str, token, lex));
	if (i > 2)
	{
		token_clean(*token);
		return (-1);
	}
	else
		(*token) = token_add((*token), token_create(str, i, lex->index++, REDIRECT_IN), NULL);
	lex->id = FD;
	return (i);
}

int	handle_and(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != '&')
			break ;
	if (i == 2)
		(*token) = token_add((*token), token_create(str, i, lex->index++, OPERATOR_AND), NULL);
	else if (i > 2 || i < 2)
	{
		token_clean(*token);
		(*token) = NULL;
		return (-1);
	}
	lex->id = CMD;
	return (i);
}

int	handle_bracket(char *str, t_token **token, t_lex *lex)
{
	if (str[0] == '(')
		(*token) = token_add((*token), token_create(str, 1, lex->index++, BRACKET_O), NULL);
	if (str[0] == ')')
		(*token) = token_add((*token), token_create(str, 1, lex->index++, BRACKET_C), NULL);
	lex->id = CMD;
	return (1);
}

#pragma endregion

#pragma region lexer

static int	handler(char *str, int *i, t_lex *lex, t_token **token)
{
	int	__return__;

	__return__ = 0;
	if (is_quote(str[*i]))
		__return__ = handle_quote(&str[*i], token, lex);
	if (str[*i] == '|')
		__return__ = handle_pipe(&str[*i], token, lex);
	if (str[*i] == '>')
		__return__ = handle_great(&str[*i], token, lex);
	if (str[*i] == '<')
		__return__ = handle_less(&str[*i], token, lex);
	if (str[*i] == '&')
		__return__ = handle_and(&str[*i], token, lex);
	if (is_alpha(str[*i]))
		 __return__ = handle_word(&str[*i], token, lex);
	if (str[*i] == '(' || str[*i] == ')')
		__return__ = handle_bracket(&str[*i], token, lex);		
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
	t_lex	lex;

	i = 0;
	lex.index = 0;
	lex.id = CMD;
	token = NULL;
	while (str[i])
		if (handler(str, &i, &lex, &token) < 0)
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
