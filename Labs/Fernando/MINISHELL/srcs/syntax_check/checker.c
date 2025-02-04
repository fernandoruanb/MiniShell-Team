/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:08:11 by fruan-ba          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/03 16:12:19 by jopereir         ###   ########.fr       */
=======
/*   Updated: 2025/02/03 16:22:53 by fruan-ba         ###   ########.fr       */
>>>>>>> 6e33de294b61935fdb8bfafc45e32e768f401444
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_utils
{
	char	*temp;
	char	*path;
	char	**paths;
	int	status;
	int	brackets_c;
	int	brackets_o;
}	t_utils;

// iddef enum e_id
// {
// 	PIPE,
// 	LIMITER,
// 	CMD,
// 	ARG,
// 	FD,
// 	BRACKET_O,
// 	BRACKET_C,
// 	REDIRECT_IN,
// 	REDIRECT_OUT,
// 	HEREDOC,
// 	APPEND,
// 	OPERATOR_OR,
// 	OPERATOR_AND,
// }	t_id;

// iddef struct s_token
// {
// 	char	*str;
// 	int	index;
// 	t_id	id;
// 	struct s_token	*next;
// 	struct s_token *previous;
// }	t_token;

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
	if ((lex->id == CMD || lex->id == FD) && diff_cmd(str) )
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

// t_token	*create_token(char *str, t_id id)
// {
// 	static int	index = 0;
// 	t_token	*new_token;

// 	new_token = malloc(sizeof(t_token));
// 	if (!new_token)
// 		return (NULL);
// 	index++;
// 	new_token->str = str;
// 	new_token->index = index;
// 	new_token->id = id;
// 	new_token->next = NULL;
// 	new_token->previous = NULL;
// 	return (new_token);
// }

// void	add_token(t_token **root, char *str, t_id id)
// {
// 	t_token	*new_token;
// 	t_token	*last;

// 	new_token = create_token(str, id);
// 	if (!new_token)
// 		return ;
// 	if (*root == NULL)
// 		*root = new_token;
// 	else
// 	{
// 		last = *root;
// 		while (last->next)
// 			last = last->next;
// 		last->next = new_token;
// 		new_token->previous = last;
// 	}
// }

void	free_tokens(t_token *root)
{
	t_token	*temp;

	while (root)
	{
		temp = root->next;
		root->next = NULL;
		root->previous = NULL;
		free(root);
		root = temp;
	}
	root = NULL;
}

char	*get_token(t_id id)
{
	static char	*ids[] =
	{
		"PIPE",
		"LIMITER",
		"CMD",
		"ARG",
		"FD",
		"BRACKET_O",
		"BRACKET_C",
		"REDIRECT_IN",
		"REDIRECT_OUT",
		"HEREDOC",
		"APPEND",
		"OPERATOR_OR",
		"OPERATOR_AND"
	};
	if (id >= 0 && id <= OPERATOR_AND)
		return (ids[id]);
	else
		return (NULL);
}

void	show_tokens(t_token *root)
{
	int	index;

	index = 1;
	while (root)
	{
		printf("TOKEN %d\n", root->index);
		printf("str: %s\nid: %s\n", root->str, get_token(root->id));
		if (root->next)
			printf("Next: %s\n", root->next->str);
		else
			printf("Next: NULL\n");
		if (root->previous)
			printf("Previous: %s\n", root->previous->str);
		else
			printf("Previous: NULL\n");
		root = root->next;
	}
}

int	free_strs_flag(char *str1, char *str2, int flag)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (flag == 1)
		return (1);
	return (0);
}

void	show_paths(t_utils *data)
{
	int	index;

	index = 0;
	while (data->paths[index] != NULL)
		printf("%s\n", data->paths[index++]);
}

void	get_paths(char **envp, t_utils *data)
{
	int	index;

	index = 0;
	while (envp[index] && (!ft_strnstr(envp[index], "PATH", 4)))
		index++;
	data->paths = ft_split(envp[index] + 5, ':');
	if (!data->paths)
		return ;
}

void	get_full_path(t_token *root, int index, t_utils *data)
{
	if (data->temp)
		free(data->temp);
	if (data->path)
		free(data->path);
	data->temp = ft_strjoin(data->paths[index], "/");
	if (!data->temp)
		return ;
	data->path = ft_strjoin(data->temp, root->str);
}

int	check_absolute_path(t_token *root, t_utils *data)
{
	if (access(root->str, F_OK | X_OK) == 0)
	{
		data->status = 1;
		return (1);
	}
	return (0);
}

int	exist_command(t_token *root, t_utils *data)
{
	int	index;

	index = 0;
	while (data->paths[index] != NULL)
	{
		get_full_path(root, index, data);
		if (!data->path)
			return (0);
		if (access(data->path, F_OK | X_OK) == 0)
		{
			data->status = 1;
			return (1);
		}
		index++;
	}
	return (0);
}

int	free_each_split(char **split1, char **split2, int flag)
{
	int	index;

	if (split1 && *split1)
	{
		index = 0;
		while (split1[index] != NULL)
		{
			free(split1[index]);
			index++;
		}
	}
	if (split2 && *split2)
	{
		index = 0;
		while (split2[index] != NULL)
		{
			free(split2[index]);
			index++;
		}
	}
	if (flag == 1)
		return (1);
	return (0);
}

int	show_error_fd(char *message, int flag, t_utils *data, int signal)
{
	ft_putendl_fd(message, 2);
	if (signal == 1)
		data->status++;
	if (flag == 1)
		return (1);
	return (0);
}

int	decrement_status(t_utils *data)
{
	data->status = 1;
	return (1);
}

int	case_pipe(t_token *root, t_utils *data)
{
	if (data->status == 0)
		return (show_error_fd("Pipe is the first to appear.", 0, data, 0));
	data->status = 2;
	if ((root->id == PIPE) && (root->previous == NULL
		|| root->next == NULL))
		return (show_error_fd("PIPE Error without next or previous", 0, data, 0));
	else if (data->status != 0 && root->next->id != CMD)
		return (show_error_fd("PIPE next elements isn't a CMD", 0, data, 0));
	return (1);
}

int	heredoc_or_append(t_token *root, t_utils *data)
{
	if (root->id == HEREDOC && root->next != NULL && root->next->id == LIMITER)
	{
		data->status = 2;
		return (1);
	}
	if (root->id == HEREDOC && root->previous != NULL && root->previous->id == CMD
		&& root->next != NULL && root->next->id == LIMITER)
		return (1);
	if (root->id == HEREDOC && root->previous != NULL && root->previous->id == ARG
		&& root->next != NULL && root->next->id == LIMITER)
		return (1);
	if (root->id == APPEND && root->next != NULL && root->next->id == FD)
		return (1);
	if (root->id == HEREDOC && root->next != NULL 
		&& root->next->id == LIMITER && root->previous != NULL
		&& root->previous->id == CMD)
		return (1);
	return (show_error_fd("Invalid case of heredoc, append", 0, data, 0));
}

int	case_redirect(t_token *root, t_utils *data)
{
	if (root->id == HEREDOC || root->id == APPEND)
		return (heredoc_or_append(root, data));
	if (data->status == 0)
		return (show_error_fd("An invalid redirect first position", 0, data, 0));
	data->status = 2;
	if (root->id == REDIRECT_IN && root->previous->id == CMD
		&& root->next != NULL && root->next->id == FD)
		return (1);
	if (root->id == REDIRECT_IN && root->next != NULL
		&& root->next->id == FD)
		return (1);
	if (root->id == REDIRECT_OUT && root->next == NULL)
		return (show_error_fd("Forgot a file after red_out", 0, data, 0));
	if (root->id == REDIRECT_OUT && root->next->id != FD)
		return (show_error_fd("Forgot a file after red_out", 0, data, 0));
	if (root->id == REDIRECT_OUT && root->next->id == FD)
		return (1);
	return (show_error_fd("Invalid case of redirects", 0, data, 0));
}

int	is_number(t_token *root)
{
	int	index;

	index = 0;
	while (root->str[index] != '\0')
	{
		if (!ft_isdigit(root->str[index]))
			return (0);
		index++;
	}
	return (1);
}

int	case_fd(t_token *root, t_utils *data)
{
	int	check_fd;

	if (is_number(root))
	{
		check_fd = ft_atoi(root->str);
		if (check_fd > 4194304)
			return (show_error_fd("Too extreme file descriptor", 0, data, 0));
	}
	if ((data->status == 0) && (!is_number(root)))
		return (show_error_fd("Isolated fd", 0, data, 0));
	data->status = 2;
	if (is_number(root) && root->next != NULL && root->next->id == REDIRECT_IN)
		return (1);
	if (root->id == FD && root->next != NULL && root->next->id == REDIRECT_OUT)
		return (1);
	if (root->id == FD && root->previous == NULL)
	       return (show_error_fd("Isolated FD without redirect", 0, data, 0));
	else if ((root->id == FD) && (root->previous != NULL)
		&& (root->previous->id == REDIRECT_OUT
		|| root->previous->id == APPEND || root->previous->id == REDIRECT_IN))
		return (1);
	return (show_error_fd("Invalid case of files", 0, data, 0));
}

int	check_invalid_things(t_token *root)
{
	if ((root->id == OPERATOR_AND || root->id == OPERATOR_OR)
		&& (root->next != NULL) && (root->previous != NULL)
		&& (root->next->id == PIPE || root->previous->id == PIPE
		|| root->next->id == OPERATOR_AND || root->previous->id == OPERATOR_AND
		|| root->next->id == OPERATOR_OR || root->previous->id == OPERATOR_OR
		|| root->next->id == APPEND || root->previous->id == APPEND
		|| root->next->id == HEREDOC || root->previous->id == HEREDOC
		|| root->next->id == REDIRECT_IN || root->previous->id == REDIRECT_IN
		|| root->next->id == REDIRECT_OUT || root->previous->id == REDIRECT_OUT))
		return (1);
	return (0);
}

int	check_brackets(t_token *root, t_utils *data)
{
	if (root->id == BRACKET_C)
		data->brackets_c++;
	else if (root->id == BRACKET_O)
		data->brackets_o++;
	data->status = 2;
	if (root->id == BRACKET_O && root->next != NULL 
		&& root->next->id == BRACKET_C)
		return (show_error_fd("You forgot to put things inside brackets", 0, data, 0));
	if (root->id == BRACKET_O && root->next != NULL && root->next->id == ARG)
		return (show_error_fd("You forgot to put a CMD inside BRACKET_O", 0, data, 0));
	if (root->id == BRACKET_C && root->next == NULL && data->brackets_o != data->brackets_c)
		return (show_error_fd("Isolated BRACKET_C", 0, data, 0));
	return (1);
}

int	extra_cases(t_token *root, t_utils *data)
{
	if (root->id == BRACKET_O || root->id == BRACKET_C)
		return (check_brackets(root, data));
	if (root->next == NULL && data->brackets_o != data->brackets_c)
		return (show_error_fd("You forgot to close brackets", 0, data, 0));
	if (root->id == OPERATOR_AND && data->status == 0)
		return (show_error_fd("Operator_AND was the first", 0, data, 0));
	if (root->id == OPERATOR_OR && data->status == 0)
		return (show_error_fd("Operator_OR was the first", 0, data, 0));
	data->status = 2;
	if (check_invalid_things(root))
		return (show_error_fd("Operators and delimiters are joking", 0, data, 0));
	if ((root->id == OPERATOR_AND) && (root->previous == NULL
		|| root->next == NULL))
		return (show_error_fd("Operator_AND without complements", 0, data, 0));
	if ((root->id == OPERATOR_OR) && (root->previous == NULL
		|| root->next == NULL))
		return (show_error_fd("Operator_OR without complements", 0, data, 0));
	return (1);
}

int	case_builtins(t_token *root)
{
	if (ft_strcmp(root->str, "cd") == 0)
		return (1);
	else if (ft_strcmp(root->str, "export") == 0)
		return (1);
	else if (ft_strcmp(root->str, "unset") == 0)
		return (1);
	else if (ft_strcmp(root->str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(root->str, "env") == 0)
		return (1);
	else if (ft_strcmp(root->str, "echo") == 0)
		return (1);
	else if (ft_strcmp(root->str, "exit") == 0)
		return (1);
	else if (ft_strcmp(root->str, "clear") == 0)
		return (1);
	return (0);
}

int	case_command(t_token *root, t_utils *data)
{
	if ((root->id == CMD && data->status > 1) && (exist_command(root, data)
			|| check_absolute_path(root, data)))
		return (decrement_status(data));
	else if (case_builtins(root))
	{
		data->status = 1;
		return (1);
	}
	else if (root->previous != NULL && ft_strcmp(root->previous->str, "xargs") == 0)
		return (1);
	else if (root->id == CMD && check_absolute_path(root, data))
		return (1);
	else if (root->id == CMD && root->next != NULL &&
		root->previous != NULL && root->previous->id == PIPE
		&& root->next->id == PIPE)
		return (1);
	else if (root->id == CMD && data->status == 1)
		return (show_error_fd("CMD received in ARG mode", 0, data, 0));
	else if ((root->id == CMD && exist_command(root, data))
		|| check_absolute_path(root, data))
		return (1);
	return (show_error_fd("Unknown CMD syntax", 0, data, 0));
}

int	case_limiter(t_token *root, t_utils *data)
{
	if (data->status == 0)
		return (show_error_fd("LIMITER is the first to appear!", 0, data, 0));
	data->status = 2;
	if (root->id == LIMITER && root->previous != NULL && root->previous->id == HEREDOC
		&& root->next != NULL && root->next->id != LIMITER)
		return (1);
	if (root->id == LIMITER && root->previous != NULL && root->previous->id == HEREDOC
		&& root->next == NULL)
		return (1);
	return (show_error_fd("Invalid LIMITER Case", 0, data, 0));
}

int	get_command(t_token *root, t_utils *data)
{
	if (root->id == PIPE)
		return (case_pipe(root, data));
	else if (root->id == LIMITER)
		return (case_limiter(root, data));
	else if (root->id == OPERATOR_AND 
		|| root->id == OPERATOR_OR || root->id == BRACKET_O || root->id == BRACKET_C)
		return (extra_cases(root, data));
	else if (root->id == REDIRECT_IN || root->id == REDIRECT_OUT
			|| root->id == APPEND || root->id == HEREDOC)
			return (case_redirect(root, data));
	else if (root->id == FD)
		return (case_fd(root, data));
	else if (root->id == CMD)
		return (case_command(root, data));
	else if (root->id != CMD && data->status == 0)
		return (show_error_fd("The first argument isn't a CMD", 0, data, 0));
	else if (root->next == NULL && data->brackets_o != data->brackets_c)
		return (show_error_fd("You forgot to close brackets", 0, data, 0));
	else if (root->id == ARG && data->status == 1)
		return (1);
	return (show_error_fd("Unfortunately, we don't know what we need to do", 0, data, 0));
}

int	check_syntax(t_token *root, char **envp, t_utils *data)
{
	int	flag;

	get_paths(envp, data);
	if (!data->paths)
		return (0);
	flag = 1;
	while (root)
	{
		//printf("TOKEN PASSED: %d\n", root->index);
		if (get_command(root, data))
			root = root->next;
		else
		{
			flag = 0;
			break ;
		}
	}
	if (flag != 1)
		return (0);
	return (1);
}

void	clean_program(t_token *root, t_utils *data)
{
	if (data->temp)
		free(data->temp);
	if (data->path)
		free(data->path);
	if (data->paths)
		free_splits(NULL, data->paths, NULL, NULL);
	free_tokens(root);
}

void	init_utils(t_utils *data)
{
	data->brackets_o = 0;
	data->brackets_c = 0;
	data->path = NULL;
	data->paths = NULL;
	data->temp = NULL;
	data->status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_utils	data;
	t_token	*root;
	char	*input;

	(void)argv;
	if (argc != 1)
		return (1);
	while (1)
	{
		input = readline("\033[1;33m<<Master>>$ \033[0m");
		root = lexer(input);
		add_history(input);
		init_utils(&data);
		//show_tokens(root);
		token_print(root);
		if (root && check_syntax(root, envp, &data))
			printf("OK\n");
		else if (root)
			printf("KO\n");
		free(input);
	}
	clean_program(NULL, &data);
	token_clean(root);
	return (0);
}
