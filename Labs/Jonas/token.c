/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:48:06 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/30 15:46:32 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef enum e_id
{
	PIPE,
	CMD,
	ARG,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	APPEND
}	t_id;

typedef struct s_token
{
	char			*str;
	t_id			id;
	int				index;

	struct s_token	*next;
}	t_token;

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

t_token	*token_create(char *str, int n, int index,  t_id id)
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

t_token	*tag_operator(t_token *token, char *str, int index)
{
	int	i;

	i = 0;
	while (str[i] && i < 2)
	{
		if (str[i] == '|')
			return (token_add(token, token_create("|", 2, index,  PIPE)));
		if (str[i] == '>' && str[i + 1] != '<')
			return (token_add(token, token_create(">", 2, index,  REDIRECT_OUT)));
		if (str[i] == '<' && str[i + 1] != '>')
			return (token_add(token, token_create("<", 2, index,  REDIRECT_IN)));
		if (str[i] == '>' && str[i + 1] == '>')
			return (token_add(token, token_create(">>", 3, index, APPEND)));
		if (str[i] == '<' && str[i + 1] == '<')
			return (token_add(token, token_create("<<", 3, index, HEREDOC)));
		i++;
	}
	return (NULL);
}

t_token	*tag_text(t_token *token, char *str, int i, int start, int index)
{
	if (str[start - 1] == '<' || str[start - 1] == '>' && i > start)
		return (token_add(token, token_create(str + start, i - start, index, ARG)));
	return (token_add(token, token_create(str + start, i - start, index, CMD)));
}

static int	is_sep(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token	*lexer(char *str)
{
	t_token	*token;
	int		i;
	int		start;
	int		index;

	token = NULL;
	start = 0;
	i = 0;
	index = 0;
	while (str[i]){
		if (is_sep(str[i]))
		{
			if (i > start)
				token = tag_text(token, str, i, start, index++);
			token = tag_operator(token, &str[i], index++);
			start = i + 1;
		}
		i++;
	}
	if (i > start)
		token = tag_text(token, str, i, start, index++);
	return (token);
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

int	main(int argc, char **argv)
{
	t_token	*tokens;

	if (argc != 2)
		return (1);
	tokens = lexer(argv[1]);
	token_print(tokens);
	printf("Tamanho do token: %d\n", token_len(tokens));
	token_clean(tokens);
	return (0);
}
