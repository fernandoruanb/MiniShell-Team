/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_copy_copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:08:11 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 11:10:15 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// typedef struct s_utils
// {
// 	char	*temp;
// 	char	*path;
// 	char	**paths;
// 	int	status;
// 	int	brackets_c;
// 	int	brackets_o;
// }	t_utils;

// typedef enum e_id
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

// typedef struct s_token
// {
// 	unsigned char	*str;
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
	NONE,
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

t_token	*token_add(t_token *token, t_token *new, t_token *prev)
{
	if (!token)
	{
		new->previous = prev;
		return (new);
	}
	token->next = token_add(token->next, new, token);
	return (token);
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


// t_token	*create_token(unsigned char *str, t_id id)
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

// void	add_token(t_token **token, unsigned char *str, t_id id)
// {
// 	t_token	*new_token;
// 	t_token	*last;

// 	new_token = create_token(str, id);
// 	if (!new_token)
// 		return ;
// 	if (*token == NULL)
// 		*token = new_token;
// 	else
// 	{
// 		last = *token;
// 		while (last->next)
// 			last = last->next;
// 		last->next = new_token;
// 		new_token->previous = last;
// 	}
// }

#pragma region Fernando

#include "../../includes/minishell.h"

typedef struct s_utils
{
	char	*temp;
	char	*path;
	char	**paths;
	int	status;
	int	redirects;
	int	files;
	int	commands;
	int	pipes;
	int	args;
	int	brackets_c;
	int	brackets_o;
	int	index_bra_c;
	int	index_bra_o;
	char	*new_str;
	struct stat	stat_check;
}	t_utils;

// typedef enum e_id
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

// typedef struct s_tokens
// {
// 	char	*str;
// 	int	index;
// 	t_id	id;
// 	struct s_tokens	*next;
// 	struct s_tokens *previous;
// }	t_token;

t_token	*create_token(char *str, t_id id)
{
	static int	index = 0;
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	index++;
	new_token->str = str;
	new_token->index = index;
	new_token->id = id;
	new_token->next = NULL;
	new_token->previous = NULL;
	return (new_token);
}

void	add_token(t_token **token, char *str, t_id id)
{
	t_token	*new_token;
	t_token	*last;

	new_token = create_token(str, id);
	if (!new_token)
		return ;
	if (*token == NULL)
		*token = new_token;
	else
	{
		last = *token;
		while (last->next)
			last = last->next;
		last->next = new_token;
		new_token->previous = last;
	}
}

void	free_tokens(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token->next;
		token->next = NULL;
		token->previous = NULL;
		free(token);
		token = temp;
	}
	token = NULL;
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

void	show_tokens(t_token *token)
{
	int	index;

	index = 1;
	while (token)
	{
		printf("TOKEN %d\n", token->index);
		printf("str: %s\nid: %s\n", token->str, get_token(token->id));
		if (token->next)
			printf("Next: %s\n", token->next->str);
		else
			printf("Next: NULL\n");
		if (token->previous)
			printf("Previous: %s\n", token->previous->str);
		else
			printf("Previous: NULL\n");
		token = token->next;
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

void	get_full_path(t_token *token, int index, t_utils *data)
{
	if (data->temp)
		free(data->temp);
	if (data->path)
		free(data->path);
	data->temp = ft_strjoin(data->paths[index], "/");
	if (!data->temp)
		return ;
	data->path = ft_strjoin(data->temp, token->str);
}

int	check_absolute_path(t_token *token, t_utils *data)
{
	if (access(token->str, F_OK | X_OK) == 0)
	{
		data->status = 1;
		return (1);
	}
	return (0);
}

int	exist_command(t_token *token, t_utils *data)
{
	int	index;

	index = 0;
	while (data->paths[index] != NULL)
	{
		get_full_path(token, index, data);
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

int	case_pipe(t_token *token, t_utils *data)
{
	if (data->status == 0)
		return (show_error_fd("Pipe is the first to appear.", 0, data, 0));
	data->status = 2;
	if (token->next != NULL && token->next->id == BRACKET_O)
		return (1);
	if (token->next != NULL && (token->next->id == REDIRECT_OUT 
		|| token->next->id == REDIRECT_IN || token->next->id == APPEND 
		|| token->next->id == HEREDOC))
		return (1);
	if ((token->id == PIPE) && (token->previous == NULL
		|| token->next == NULL))
		return (show_error_fd("PIPE Error without next or previous", 0, data, 0));
	else if (data->status != 0 && token->next->id != CMD)
		return (show_error_fd("PIPE next elements isn't a CMD", 0, data, 0));
	return (1);
}

int	heredoc_or_append(t_token *token, t_utils *data)
{
	if (token->id == HEREDOC && token->next != NULL && token->next->id == LIMITER)
	{
		data->status = 2;
		return (1);
	}
	if (token->id == HEREDOC && token->previous != NULL && token->previous->id == CMD
		&& token->next != NULL && token->next->id == LIMITER)
		return (1);
	if (token->id == HEREDOC && token->previous != NULL && token->previous->id == ARG
		&& token->next != NULL && token->next->id == LIMITER)
		return (1);
	if (token->id == APPEND && token->next != NULL && (token->next->id == FD))
	{
		data->status = 2;
		return (1);
	}
	if (token->id == HEREDOC && token->next != NULL 
		&& token->next->id == LIMITER && token->previous != NULL
		&& token->previous->id == CMD)
		return (1);
	return (show_error_fd("Invalid case of heredoc, append", 0, data, 0));
}

int	extra_redirect_cases(t_token *token, t_utils *data)
{
	if ((token->id == REDIRECT_IN || token->id == REDIRECT_OUT || token->id == APPEND)
		&& token->next != NULL && token->next->id == FD)
		return (1);
	return (show_error_fd("Invalid case of redirects", 0, data, 0));
}

int	case_redirect(t_token *token, t_utils *data)
{
	if (token->id == HEREDOC || token->id == APPEND)
		return (heredoc_or_append(token, data));
	if (data->status == 0 && (token->id == REDIRECT_IN || token->id == REDIRECT_OUT
		|| token->id == APPEND) && token->next != NULL && token->next->id == FD)
	{
		data->status = 2;
		return (1);
	}
	data->status = 2;
	if (token->id == REDIRECT_IN && token->previous != NULL 
		&& token->previous->id == CMD && token->next != NULL 
		&& token->next->id == FD)
		return (1);
	if (token->id == REDIRECT_IN && token->next != NULL
		&& token->next->id == FD)
		return (1);
	if (token->id == REDIRECT_OUT && token->next == NULL)
		return (show_error_fd("Forgot a file after red_out", 0, data, 0));
	if (token->id == REDIRECT_OUT && token->next != NULL 
		&& token->next->id != FD)
		return (show_error_fd("Forgot a file after red_out", 0, data, 0));
	if (token->id == REDIRECT_OUT && token->next->id == FD)
		return (1);
	return (extra_redirect_cases(token, data));
}

int	is_number(t_token *token, t_utils *data)
{
	int	index;

	index = 0;
	while (token->str[index] != '\0')
	{
		if (!ft_isdigit(token->str[index]))
			return (0);
		index++;
	}
	data->files--;
	return (1);
}

int	check_is_valid_fd(t_token *token, t_utils *data)
{
	long	check_fd;

	check_fd = ft_atoi(token->str);
	if (check_fd > 2147483647)
		return (show_error_fd("Too extreme file descriptor", 0, data, 0));
	return (1);
}

int	check_is_directory(t_token *token, t_utils *data)
{

	if (stat(token->str, &data->stat_check) == -1)
		return (0);
	if (S_ISDIR(data->stat_check.st_mode))
		return (1);
	return (0);
}

int	case_fd(t_token *token, t_utils *data)
{
	if (is_number(token, data))
		return (check_is_valid_fd(token, data));
	if (check_is_directory(token, data))
		return (show_error_fd("You put a directory as file", 0, data, 0));
	if ((data->status == 0) && (!is_number(token, data)))
		return (show_error_fd("Isolated fd", 0, data, 0));
	data->status = 2;
	if (is_number(token, data) && token->next != NULL && token->next->id == REDIRECT_IN)
		return (1);
	if (token->id == FD && token->next != NULL && token->next->id == REDIRECT_OUT)
		return (1);
	if (token->id == FD && token->previous == NULL)
	       return (show_error_fd("Isolated FD without redirect", 0, data, 0));
	else if ((token->id == FD) && (token->previous != NULL)
		&& (token->previous->id == REDIRECT_OUT
		|| token->previous->id == APPEND || token->previous->id == REDIRECT_IN))
		return (1);
	else if (token->previous != NULL && token->previous->id == ARG)
		return (1);
	return (show_error_fd("Invalid case of files", 0, data, 0));
}

int	check_invalid_things(t_token *token)
{
	if ((token->id == OPERATOR_AND || token->id == OPERATOR_OR)
		&& (token->next != NULL) && (token->previous != NULL)
		&& (token->next->id == PIPE || token->previous->id == PIPE
		|| token->next->id == OPERATOR_AND || token->previous->id == OPERATOR_AND
		|| token->next->id == OPERATOR_OR || token->previous->id == OPERATOR_OR))
		return (1);
	return (0);
}

int	check_brackets(t_token *token, t_utils *data)
{
	if (token->id == BRACKET_C)
		data->brackets_c++;
	else if (token->id == BRACKET_O)
		data->brackets_o++;
	data->status = 2;
	if (token->id == BRACKET_O && token->next != NULL 
		&& token->next->id == BRACKET_C)
		return (show_error_fd("You forgot to put things inside brackets", 0, data, 0));
	if (token->id == BRACKET_O && token->next != NULL && token->next->id == ARG)
		return (show_error_fd("You forgot to put a CMD inside BRACKET_O", 0, data, 0));
	if (token->id == BRACKET_C && token->next == NULL && data->brackets_o != data->brackets_c)
		return (show_error_fd("Isolated BRACKET_C", 0, data, 0));
	return (1);
}

int	extra_cases(t_token *token, t_utils *data)
{
	if (token->id == BRACKET_O || token->id == BRACKET_C)
		return (check_brackets(token, data));
	if (token->next == NULL && data->brackets_o != data->brackets_c)
		return (show_error_fd("You forgot to close brackets", 0, data, 0));
	if (token->id == OPERATOR_AND && data->status == 0)
		return (show_error_fd("Operator_AND was the first", 0, data, 0));
	if (token->id == OPERATOR_OR && data->status == 0)
		return (show_error_fd("Operator_OR was the first", 0, data, 0));
	data->status = 2;
	if (check_invalid_things(token))
		return (show_error_fd("Operators and delimiters are joking", 0, data, 0));
	if ((token->id == OPERATOR_AND) && (token->previous == NULL
		|| token->next == NULL))
		return (show_error_fd("Operator_AND without complements", 0, data, 0));
	if ((token->id == OPERATOR_OR) && (token->previous == NULL
		|| token->next == NULL))
		return (show_error_fd("Operator_OR without complements", 0, data, 0));
	return (1);
}

int	case_builtins(t_token *token)
{
	if (ft_strcmp(token->str, "cd") == 0)
		return (1);
	else if (ft_strcmp(token->str, "export") == 0)
		return (1);
	else if (ft_strcmp(token->str, "unset") == 0)
		return (1);
	else if (ft_strcmp(token->str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(token->str, "env") == 0)
		return (1);
	else if (ft_strcmp(token->str, "echo") == 0)
		return (1);
	else if (ft_strcmp(token->str, "exit") == 0)
		return (1);
	else if (ft_strcmp(token->str, "clear") == 0)
		return (1);
	return (0);
}
int	case_builtins_quotes(t_utils *data)
{
	if (ft_strcmp(data->new_str, "cd") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "export") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "unset") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "env") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "echo") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "exit") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "clear") == 0)
		return (1);
	return (0);
}

int	is_absolute_path_quotes(t_utils *data)
{
	if (access(data->new_str, F_OK | X_OK) == 0)
		return (1);
	return (0);
}

int	test_all_paths(t_utils *data)
{
	int	index;

	index = 0;
	while (data->paths[index] != NULL)
	{
		if (data->temp)
			free(data->temp);
		if (data->path)
			free(data->path);
		data->temp = ft_strjoin(data->paths[index], "/");
		if (!data->temp)
			return (0);
		data->path = ft_strjoin(data->temp, data->new_str);
		if (!data->path)
			return (0);
		if (access(data->path, F_OK | X_OK) == 0)
			return (1);
		index++;
	}
	if (case_builtins_quotes(data))
		return (1);
	if (is_absolute_path_quotes(data))
		return (1);
	return (0);
}

int	is_insider_quotes(t_token *root, t_utils *data)
{
	size_t	length;

	if (data->new_str)
		free(data->new_str);
	if (!root)
		return (0);
	length = ft_strlen(root->str);
	if ((root->str[0] == '\'' && root->str[length - 1] == '\'')
		|| (root->str[0] == '\"' && root->str[length - 1] == '\"'))
	{
		data->new_str = ft_substr(root->str, 1, length - 2);
		if (!data->new_str)
			return (0);
		ft_printf("A new_str: %s\n", data->new_str);
		if (test_all_paths(data))
			return (1);
	}
	return (0);
}

int	is_environment(t_token *token)
{
	if (ft_strncmp(token->str, "$", 1) == 0)
		return (1);
	return (0);
}

int	case_command(t_token *token, t_utils *data)
{
	if ((token->id == CMD && data->status > 1) && (exist_command(token, data)
			|| check_absolute_path(token, data)))
		return (decrement_status(data));
	else if (case_builtins(token) || is_environment(token)
			|| is_insider_quotes(token, data))
	{
		data->status = 1;
		return (1);
	}
	else if (token->previous != NULL && ft_strcmp(token->previous->str, "xargs") == 0)
		return (1);
	else if (token->id == CMD && check_absolute_path(token, data))
		return (1);
	else if (token->id == CMD && token->next != NULL &&
		token->previous != NULL && token->previous->id == PIPE
		&& token->next->id == PIPE)
		return (1);
	else if (token->id == CMD && data->status == 1)
		return (show_error_fd("CMD received in ARG mode", 0, data, 0));
	else if ((token->id == CMD && exist_command(token, data))
		|| check_absolute_path(token, data))
		return (1);
	return (show_error_fd("Unknown CMD syntax", 0, data, 0));
}

int	case_limiter(t_token *token, t_utils *data)
{
	if (data->status == 0)
		return (show_error_fd("LIMITER is the first to appear!", 0, data, 0));
	data->status = 2;
	if (token->id == LIMITER && token->previous != NULL && token->previous->id == HEREDOC
		&& token->next != NULL && token->next->id != LIMITER)
		return (1);
	if (token->id == LIMITER && token->previous != NULL && token->previous->id == HEREDOC
		&& token->next == NULL)
		return (1);
	return (show_error_fd("Invalid LIMITER Case", 0, data, 0));
}

int	case_arg(t_token *token, t_utils *data)
{
	if (token->id == ARG && data->status == 1)
		return (1);
	else if (token->id == ARG && token->previous != NULL && (token->previous->id == FD
		|| token->previous->id == REDIRECT_OUT || token->previous->id == REDIRECT_IN
		|| token->previous->id == APPEND || token->previous->id == ARG))
		return (1);
	else if (token->id == ARG && token->next != NULL && (token->next->id == ARG
			|| token->next->id == FD))
		return (1);
	else if (token->id == ARG && token->previous != NULL && token->previous->id == LIMITER)
		return (1);
	return (show_error_fd("Invalid case of args", 0, data, 0));
}

int	check_invalid_brackets_position(t_utils *data)
{
	if (data->index_bra_o != -1 && data->index_bra_c != -1)
	{
		if (data->index_bra_o > data->index_bra_c)
			return (1);
		else
		{
			data->index_bra_o = -1;
			data->index_bra_c = -1;
		}
	}
	return (0);
}

int	final_case(t_token *token, t_utils *data)
{
	if (token->id == REDIRECT_IN || token->id == APPEND || token->id == REDIRECT_OUT)
		data->redirects++;
	if (token->id == FD)
		data->files++;
	if (token->id == CMD)
		data->commands++;
	if (token->id == ARG)
		data->args++;
	if (token->id == PIPE)
		data->pipes++;
	if (token->id == BRACKET_C)
		data->index_bra_c = token->index;
	if (token->id == BRACKET_O)
		data->index_bra_o = token->index;
	if (token->next == NULL && data->redirects != data->files)
		return (1);
	if (token->next == NULL && data->commands == 0 && data->args > 0)
		return (show_error_fd("You put args but never a command", 1, data, 0));
	if (token->next == NULL && data->commands < data->pipes)
	       return (show_error_fd("You have so many pipes than commands.", 1, data, 0));
	if (check_invalid_brackets_position(data))
		return (show_error_fd("You inverted the position of brackets", 1, data, 0));
	return (0);
}

int	get_command(t_token *token, t_utils *data)
{
	if (final_case(token, data))
		return (show_error_fd("Final case Error", 0, data, 0));
	if (token->id == PIPE)
		return (case_pipe(token, data));
	else if (token->id == LIMITER)
		return (case_limiter(token, data));
	else if (token->id == OPERATOR_AND 
		|| token->id == OPERATOR_OR || token->id == BRACKET_O || token->id == BRACKET_C)
		return (extra_cases(token, data));
	else if (token->id == REDIRECT_IN || token->id == REDIRECT_OUT
			|| token->id == APPEND || token->id == HEREDOC)
			return (case_redirect(token, data));
	else if (token->id == FD)
		return (case_fd(token, data));
	else if (token->id == CMD)
		return (case_command(token, data));
	else if (token->id != CMD && data->status == 0)
		return (show_error_fd("The first argument isn't a CMD", 0, data, 0));
	if (token->next == NULL && data->brackets_o != data->brackets_c)
		return (show_error_fd("You forgot to close brackets", 0, data, 0));
	if (token->id == ARG)
		return (case_arg(token, data));
	return (show_error_fd("Unfortunately, we don't know what we need to do", 0, data, 0));
}

int	check_syntax(t_token *token, char **envp, t_utils *data)
{
	int	flag;

	get_paths(envp, data);
	if (!data->paths)
		return (0);
	flag = 1;
	while (token)
	{
	//	printf("TOKEN PASSED: %d\n", token->index);
		if (get_command(token, data))
			token = token->next;
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

void	clean_program(t_token *token, t_utils *data)
{
	if (data->temp)
		free(data->temp);
	if (data->path)
		free(data->path);
	if (data->new_str)
		free(data->new_str);
	if (data->paths)
		free_splits(NULL, data->paths, NULL, NULL);
	free_tokens(token);
}

void	init_utils(t_utils *data)
{
	data->index_bra_c = -1;
	data->index_bra_o = -1;
	data->brackets_o = 0;
	data->brackets_c = 0;
	data->new_str = NULL;
	data->path = NULL;
	data->paths = NULL;
	data->temp = NULL;
	data->status = 0;
	data->redirects = 0;
	data->pipes = 0;
	data->args = 0;
	data->commands = 0;
	data->files = 0;
}

#pragma endregion

#pragma region Check

int	is_quote(unsigned char c)
{
	return (c == '\'' || c == '\"' || c == '\\');
}

int	is_word(unsigned char c)
{
	return ((c != ' ' && c != '&' && c != '|' && c != '(' && c != ')'
			&& c != '<' && c != '>') && !(is_quote(c)));
}

int	is_pipe(unsigned char c)
{
	return (c == '|');
}

int	is_great(unsigned char c)
{
	return (c == '>');
}

int	is_less(unsigned char c)
{
	return (c == '<');
}

int	is_num(unsigned char c)
{
	return (c >= '0' && c <= '9');
}

#pragma endregion

typedef struct s_lex
{
	t_id	id;
	char	*path;
	int		index;

	char	**envp;
	char	*word;
}	t_lex;

#pragma region Handles 

int	diff_cmd(char *str)
{
	return (ft_strncmp(str, "xargs", 5) != 0);
}


void	*clear_split(char **str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
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

int	is_cmd(char *str, t_lex *lex)
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

	//printf("token: %s %d\n", lex->word, (is_cmd(lex->word, lex)));
	if ((is_cmd(lex->word, lex) && lex->id != FD) || lex->id == NONE)
		lex->id = CMD;
	else if (lex->id != FD && lex->id != LIMITER && lex->id != CMD)
		lex->id = ARG;
	i = 0;	
	while (str[i] && is_word(str[i]))
		i++;
	(*token) = token_add((*token), token_create(str, i, lex->index++, lex->id), NULL);
	if ((lex->id == CMD || lex->id == FD || lex->id == LIMITER))
		lex->id = ARG;
	else if (lex->id == FD)
		lex->id = CMD;
	return (i);
}

static int	make_token(t_token **token, char *str, t_lex *lex, int *i)
{
	(*token) = token_add((*token), token_create(str, *i, lex->index++, lex->id), NULL);
	if (lex->id == FD || lex->id == LIMITER)
		lex->id = ARG;
	return (*i);
}

//orginal
int	handle_quote(char *str, t_token **token, t_lex *lex)
{
	char	quote;
	int		i;

	i = 0;
	if (lex->id == NONE)
		lex->id = CMD;
	else if (lex->id == CMD)
		lex->id = ARG;
	if (str[i] == '\\')
		i++;
	quote = str[i++];
	while (str[i])
		if (str[i++] == quote)
			return (make_token(token, str, lex, &i));
	if (str[0] == '\\')
		return (make_token(token, str, lex, &i));
	token_clean(*token);
	(*token) = NULL;
	return (-1);
}

//alterada
// int	handle_quote(unsigned char *str, t_token **token, t_lex *lex)
// {
// 	unsigned char	quote;
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
	int	i;

	i = 2;
	(*token) = token_add((*token), token_create(str, i, lex->index++, APPEND), NULL);
	lex->id = FD;
	//i += handle_word(&str[i + 1], token, lex) + 1;
	return (i);
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
	//i += handle_word(&str[i], token, lex);
	return (i);
}

int	handle_heredoc(char *str, t_token **token, t_lex *lex)
{
	int	i;

	i = 2;
	(*token) = token_add((*token), token_create(str, i, lex->index++, HEREDOC), NULL);
	lex->id = LIMITER;
	//i += handle_word(&str[i + 1], token, lex) + 1;
	return (i);
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
	//i += handle_word(&str[i], token, lex);
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

char	*get_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_word(str[i]))
		i++;
	return (ft_strndup(str, i));
}

//|| command_exits(&str[*i], lex->data)
static int	handler(char *str, int *i, t_lex *lex, t_token **token)
{
	int	__return__;
	__return__ = 0;
	lex->word = get_str(&str[*i]);
	if((str[*i + 1] == '>' || str[*i + 1] == '<') && ft_isdigit(str[*i]))
		lex->id = FD;
	if (is_quote(str[*i]))
		__return__ = handle_quote(&str[*i], token, lex);
	if (is_word(str[*i]))
		 __return__ = handle_word(&str[*i], token, lex);
	if (str[*i] == '|')
		__return__ = handle_pipe(&str[*i], token, lex);
	if (str[*i] == '>')
		__return__ = handle_great(&str[*i], token, lex);
	if (str[*i] == '<')
		__return__ = handle_less(&str[*i], token, lex);
	if (str[*i] == '&')
		__return__ = handle_and(&str[*i], token, lex);
	if (str[*i] == '(' || str[*i] == ')')
		__return__ = handle_bracket(&str[*i], token, lex);		
	if (__return__ > 0)
		*i += __return__;
	else
		(*i)++;
	return (__return__);
}

t_token	*lexer(char *str, char **envp)
{
	int		i;
	t_token	*token;
	t_lex	lex;

	i = 0;
	lex.index = 0;
	lex.id = NONE;
	lex.word = NULL;
	lex.envp = envp;
	token = NULL;
	while (str[i])
	{
		if (handler(str, &i, &lex, &token) < 0)
			return (NULL);
		if (lex.word)
			free(lex.word);
	}
	return (token);
}

#pragma endregion

int	main(int argc, char **argv, char **envp)
{
	t_utils	data;
	t_token	*token;
	char	*input;

	//(void)argv;
	if (argc != 2)
		return (1);
	//init_utils(&data);
	//get_paths(envp, &data);
	// while (1)
	// {
		//input = readline("\033[1;33m<<Master>>$ \033[0m");
		token = lexer(argv[1], envp);
		//add_history(input);
		// init_utils(&data);
		//show_tokens(token);
		token_print(token);
		// if (token == NULL)
		// 	printf("Invalid input.\n");
		// if (token && check_syntax(token, envp, &data))
		// 	printf("OK\n");
		// else if (token)
		// 	printf("KO\n");
		//free(input);
	//}
	//clean_program(NULL, &data);
	token_clean(token);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_utils	data;
// 	t_token	*token;

// 	(void)argv;
// 	if (argc < 1)
// 		return (1);
// 	token = NULL;
// 	init_utils(&data);
// 	token = create_token("cat", CMD);
// 	if (!token)
// 		return (1);
// 	add_token(&token, ">>", APPEND);
// 	add_token(&token, "infile", FD);
// 	add_token(&token, "-n", ARG);
// 	show_tokens(token);
// 	if (check_syntax(token, envp, &data))
// 		printf("OK\n");
// 	else
// 		printf("KO\n");
// 	clean_program(token, &data);
// 	return (0);
// }
