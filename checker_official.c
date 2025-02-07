/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_official.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:08:11 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 11:51:59 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	OPERATOR_AND,
}	t_id;

typedef struct s_tokens
{
	char	*str;
	int	index;
	t_id	id;
	struct s_tokens	*next;
	struct s_tokens *previous;
}	t_token;

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

void	add_token(t_token **root, char *str, t_id id)
{
	t_token	*new_token;
	t_token	*last;

	new_token = create_token(str, id);
	if (!new_token)
		return ;
	if (*root == NULL)
		*root = new_token;
	else
	{
		last = *root;
		while (last->next)
			last = last->next;
		last->next = new_token;
		new_token->previous = last;
	}
}

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
		printf("Value: %s\nid: %s\n", root->str, get_token(root->id));
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
	if (root->next != NULL && root->next->id == BRACKET_O)
		return (1);
	if (root->next != NULL && (root->next->id == REDIRECT_OUT 
		|| root->next->id == REDIRECT_IN || root->next->id == APPEND 
		|| root->next->id == HEREDOC))
		return (1);
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
	if (root->id == APPEND && root->next != NULL && (root->next->id == FD))
	{
		data->status = 2;
		return (1);
	}
	if (root->id == HEREDOC && root->next != NULL 
		&& root->next->id == LIMITER && root->previous != NULL
		&& root->previous->id == CMD)
		return (1);
	return (show_error_fd("Invalid case of heredoc, append", 0, data, 0));
}

int	extra_redirect_cases(t_token *root, t_utils *data)
{
	if ((root->id == REDIRECT_IN || root->id == REDIRECT_OUT || root->id == APPEND)
		&& root->next != NULL && root->next->id == FD)
		return (1);
	return (show_error_fd("Invalid case of redirects", 0, data, 0));
}

int	case_redirect(t_token *root, t_utils *data)
{
	if (root->id == HEREDOC || root->id == APPEND)
		return (heredoc_or_append(root, data));
	if (data->status == 0 && (root->id == REDIRECT_IN || root->id == REDIRECT_OUT
		|| root->id == APPEND) && root->next != NULL && root->next->id == FD)
	{
		data->status = 2;
		return (1);
	}
	data->status = 2;
	if (root->id == REDIRECT_IN && root->previous != NULL 
		&& root->previous->id == CMD && root->next != NULL 
		&& root->next->id == FD)
		return (1);
	if (root->id == REDIRECT_IN && root->next != NULL
		&& root->next->id == FD)
		return (1);
	if (root->id == REDIRECT_OUT && root->next == NULL)
		return (show_error_fd("Forgot a file after red_out", 0, data, 0));
	if (root->id == REDIRECT_OUT && root->next != NULL 
		&& root->next->id != FD)
		return (show_error_fd("Forgot a file after red_out", 0, data, 0));
	if (root->id == REDIRECT_OUT && root->next->id == FD)
		return (1);
	return (extra_redirect_cases(root, data));
}

int	is_number(t_token *root, t_utils *data)
{
	int	index;

	index = 0;
	while (root->str[index] != '\0')
	{
		if (!ft_isdigit(root->str[index]))
			return (0);
		index++;
	}
	data->files--;
	return (1);
}

int	check_is_valid_fd(t_token *root, t_utils *data)
{
	long	check_fd;

	check_fd = ft_atoi(root->str);
	if (check_fd > 2147483647)
		return (show_error_fd("Too extreme file descriptor", 0, data, 0));
	return (1);
}

int	check_is_directory(t_token *root, t_utils *data)
{

	if (stat(root->str, &data->stat_check) == -1)
		return (0);
	if (S_ISDIR(data->stat_check.st_mode))
		return (1);
	return (0);
}

int	case_fd(t_token *root, t_utils *data)
{
	if (is_number(root, data))
		return (check_is_valid_fd(root, data));
	if (check_is_directory(root, data))
		return (show_error_fd("You put a directory as file", 0, data, 0));
	if ((data->status == 0) && (!is_number(root, data)))
		return (show_error_fd("Isolated fd", 0, data, 0));
	data->status = 2;
	if (is_number(root, data) && root->next != NULL && root->next->id == REDIRECT_IN)
		return (1);
	if (root->id == FD && root->next != NULL && root->next->id == REDIRECT_OUT)
		return (1);
	if (root->id == FD && root->previous == NULL)
	       return (show_error_fd("Isolated FD without redirect", 0, data, 0));
	else if ((root->id == FD) && (root->previous != NULL)
		&& (root->previous->id == REDIRECT_OUT
		|| root->previous->id == APPEND || root->previous->id == REDIRECT_IN))
		return (1);
	else if (root->previous != NULL && root->previous->id == ARG)
		return (1);
	return (show_error_fd("Invalid case of files", 0, data, 0));
}

int	check_invalid_things(t_token *root)
{
	if ((root->id == OPERATOR_AND || root->id == OPERATOR_OR)
		&& (root->next != NULL) && (root->previous != NULL)
		&& (root->next->id == PIPE || root->previous->id == PIPE
		|| root->next->id == OPERATOR_AND || root->previous->id == OPERATOR_AND
		|| root->next->id == OPERATOR_OR || root->previous->id == OPERATOR_OR))
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

int	is_environment(t_token *root)
{
	if (ft_strncmp(root->str, "$", 1) == 0)
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

int	case_command(t_token *root, t_utils *data)
{
	if ((root->id == CMD && data->status > 1) && (exist_command(root, data)
			|| check_absolute_path(root, data)))
		return (decrement_status(data));
	else if (case_builtins(root) || is_environment(root)
			|| is_insider_quotes(root, data))
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

int	case_arg(t_token *root, t_utils *data)
{
	if (root->id == ARG && data->status == 1)
		return (1);
	else if (root->id == ARG && root->previous != NULL && (root->previous->id == FD
		|| root->previous->id == REDIRECT_OUT || root->previous->id == REDIRECT_IN
		|| root->previous->id == APPEND || root->previous->id == ARG))
		return (1);
	else if (root->id == ARG && root->next != NULL && (root->next->id == ARG
			|| root->next->id == FD))
		return (1);
	else if (root->id == ARG && root->previous != NULL && root->previous->id == LIMITER)
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

int	final_case(t_token *root, t_utils *data)
{
	if (root->id == REDIRECT_IN || root->id == APPEND || root->id == REDIRECT_OUT)
		data->redirects++;
	if (root->id == FD)
		data->files++;
	if (root->id == CMD)
		data->commands++;
	if (root->id == ARG)
		data->args++;
	if (root->id == PIPE)
		data->pipes++;
	if (root->id == BRACKET_C)
		data->index_bra_c = root->index;
	if (root->id == BRACKET_O)
		data->index_bra_o = root->index;
	if (root->next == NULL && data->redirects != data->files)
		return (1);
	if (root->next == NULL && data->commands == 0 && data->args > 0)
		return (show_error_fd("You put args but never a command", 1, data, 0));
	if (root->next == NULL && data->commands < data->pipes)
	       return (show_error_fd("You have so many pipes than commands.", 1, data, 0));
	if (check_invalid_brackets_position(data))
		return (show_error_fd("You inverted the position of brackets", 1, data, 0));
	return (0);
}

int	get_command(t_token *root, t_utils *data)
{
	if (final_case(root, data))
		return (show_error_fd("Final case Error", 0, data, 0));
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
	if (root->next == NULL && data->brackets_o != data->brackets_c)
		return (show_error_fd("You forgot to close brackets", 0, data, 0));
	if (root->id == ARG)
		return (case_arg(root, data));
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
	//	printf("TOKEN PASSED: %d\n", root->index);
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
	if (data->new_str)
		free(data->new_str);
	free_tokens(root);
}

void	init_utils(t_utils *data)
{
	data->index_bra_c = -1;
	data->index_bra_o = -1;
	data->brackets_o = 0;
	data->brackets_c = 0;
	data->path = NULL;
	data->paths = NULL;
	data->temp = NULL;
	data->new_str = NULL;
	data->status = 0;
	data->redirects = 0;
	data->pipes = 0;
	data->args = 0;
	data->commands = 0;
	data->files = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_utils	data;
	t_token	*root;

	(void)argv;
	if (argc < 1)
		return (1);
	root = NULL;
	init_utils(&data);
	root = create_token("\"echo\"", CMD);
	if (!root)
		return (1);
	add_token(&root, "\"hello\"", ARG);
	add_token(&root, "|", PIPE);
	add_token(&root, "<<", HEREDOC);
	add_token(&root, "jonas'", LIMITER);
	add_token(&root, "\'/bin/cat\'", CMD);
	add_token(&root, "-e", ARG);
	show_tokens(root);
	if (check_syntax(root, envp, &data))
		printf("OK\n");
	else
		printf("KO\n");
	clean_program(root, &data);
	return (0);
}
