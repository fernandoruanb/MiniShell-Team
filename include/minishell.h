/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:36:51 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/27 13:19:07 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include "libft.h"
# include "libft.h"
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <readline/history.h>

# define BLUE "\033[0;36m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RED "\033[38;5;214m"
# define RESET	"\033[0m"

typedef struct s_ast
{
	char			**cmd;
	int				index;

	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

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
}	t_id;

typedef struct s_lex
{
	t_id	id;
	char	*path;
	int		index;

	char	**envp;
	char	*word;
}	t_lex;

typedef struct s_token
{
	char			*str;
	t_id			id;
	int				index;

	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_prompt
{
	char	*input;
	char	**cmdset;
	char	*path;

	int		exit_status;
}	t_prompt;

typedef struct s_utils
{
	char		*temp;
	char		*path;
	char		**paths;
	int			status;
	int			redirects;
	int			files;
	int			commands;
	int			pipes;
	int			exit_status;
	int			simple_quotes;
	int			double_quotes;
	char		*copy_new;
	int			args;
	int			brackets_c;
	int			brackets_o;
	int			index_bra_c;
	int			index_bra_o;
	char		*new_str;
	struct stat	stat_check;
}	t_utils;

typedef struct s_export
{
	char			*name;
	char			*value;

	struct s_export	*next;
	struct s_export	*prev;
}	t_export;

typedef struct	s_var
{
	char			*name;
	char			*value;

	struct s_var	*next;
	struct s_var	*prev;
}	t_localvar;

typedef struct s_data
{
	t_ast		*root;
	t_prompt	*prompt;
	t_token		*token;
	t_utils		utils;
	t_export	*export_vars;
	t_localvar	*local_vars;

	char		**envp;
	int			is_pipe;
	int			fd[2];
}	t_data;

//	0-utils.c
void		*clear_split(char **str);
char		*ft_strndup(char *str, int n);
int			my_free_my_life(void *s1, void *s2, void *s3, int __return__);
int			splitlen(char **split);

//	1-token
t_token		*token_create(char *str, int n, int index, t_id id);
t_token		*token_add(t_token *token, t_token *new, t_token *prev);
void		token_clean(t_token *token);
/*
	temporaria, apagar antes de mandar
*/
void		token_print(t_token *token);

//	main
void		create(t_data *data, char **envp);
void		execute(t_data *data);
int			destroy(t_data *data, char *message, int exit_code);
int			init_data(t_data *data, char **envp);

//	prompt
int			child(t_prompt *prompt);
void		display_prompt(t_data *data);
void		analysis(t_data *data);

//	built_in/
void		ft_cd(char *input);
void		ft_echo(t_prompt *prompt);
char		*enviroment_var(char *cmd, int exit_status);
void		ft_exit(char *name, t_data *data, char *exit_status);
int			valid_name(char c, int flag);
int			ft_export(char *input, t_export **var);
t_export	*search_var(t_export **var, char *name);
void		ft_unset(t_export **var, t_localvar **local, char *name);
void		export_clean(t_export **var);
void		export_init(char **envp, t_export **var);
int			ft_localvar(char *input, t_localvar **var);
void		clean_locals(t_localvar	*var);
int			namevalidation(char *input);
char		*get_var(char *input);
int			export_print(t_export **var);
t_export	*export_last(t_export **var);
void		locals_print(t_localvar **var);
t_localvar	*search_locals(t_localvar **var, char *name);

//	lexer
t_token		*lexer(char *str, char **envp);
int			handle_bracket(char *str, t_token **token, t_lex *lex);
int			handle_and(char *str, t_token **token, t_lex *lex);
int			handle_less(char *str, t_token **token, t_lex *lex);
int			handle_great(char *str, t_token **token, t_lex *lex);
int			handle_word(char *str, t_token **token, t_lex *lex);
int			is_word(unsigned char c, int flag);
int			is_quote(unsigned char c);
int			handle_pipe(char *str, t_token **token, t_lex *lex);
int			quote_close(char *str);
void		get_label(t_lex *lex);
int			error_message(char *message, int __return__, t_token **token);
int			handle_fd(char *str);

// syntax checker
void		init_utils(t_utils *data);
void		clean_program(t_utils *data);
int			check_syntax(t_token *root, char **envp, t_utils *data);
int			get_command(t_token *root, t_utils *data);
int			final_case(t_token *root, t_utils *data);
int			check_invalid_brackets_position(t_utils *data);
int			case_arg(t_token *root, t_utils *data);
int			case_limiter(t_token *root, t_utils *data);
int			case_command(t_token *root, t_utils *data);
int			is_insider_quotes(t_token *root, t_utils *data);
int			test_all_paths(t_utils *data);
int			is_absolute_path_quotes(t_utils *data);
int			case_builtins_quotes(t_utils *data);
int			is_environment(t_token *root);
int			case_builtins(t_token *root);
int			extra_cases(t_token *root, t_utils *data);
int			check_brackets(t_token *root, t_utils *data);
int			check_invalid_things(t_token *root);
int			case_fd(t_token *root, t_utils *data);
int			check_is_directory(t_token *root, t_utils *data);
int			check_is_valid_fd(t_token *root, t_utils *data);
int			is_number(t_token *root);
int			case_redirect(t_token *root, t_utils *data);
int			extra_redirect_cases(t_token *root, t_utils *data);
int			heredoc_or_append(t_token *root, t_utils *data);
int			case_pipe(t_token *root, t_utils *data);
int			decrement_status(t_utils *data);
int			show_error_fd(char *message, int flag, t_utils *data, int signal);
int			free_each_split(char **split1, char **split2, int flag);
int			exist_command(t_token *root, t_utils *data);
int			check_absolute_path(t_token *root, t_utils *data);
void		get_full_path(t_token *root, int index, t_utils *data);
void		get_paths(char **envp, t_utils *data);
void		show_paths(t_utils *data);
int			free_strs_flag(char *str1, char *str2, int flag);
void		show_tokens(t_token *root);
char		*get_token(t_id id);
void		free_tokens(t_token *root);
void		add_token(t_token **root, char *str, t_id id);
t_token		*create_token(char *str, t_id id);
int			special(t_token *root, t_utils *data);
int			get_check_command(t_token *root, t_utils *data);
int			final_check(t_utils *data);
int			check_order_quotes(t_token *root);
int			case_quotes_syntax(char *quote, int marker, int *flag);
void		create_variables_order(t_token *root, int *index, int *flag);
int			special_check_quotes(t_token *root, t_utils *data);
int			how_many_quotes(t_token *root, t_utils *data);
int			ft_isalpha_special_2(char letter);
int			ft_isalpha_special(char letter);
int			check_quotes(t_token *root);
void		check_copy_new(t_utils *data);
void		init_utils(t_utils *data);
void		clean_program(t_utils *data);
int			check_syntax(t_token *root, char **envp, t_utils *data);
int			get_command(t_token *root, t_utils *data);
int			final_case(t_token *root, t_utils *data);
int			check_invalid_brackets_position(t_utils *data);
int			case_arg(t_token *root, t_utils *data);
int			case_limiter(t_token *root, t_utils *data);
int			case_command(t_token *root, t_utils *data);
int			is_insider_quotes(t_token *root, t_utils *data);
int			test_all_paths(t_utils *data);
int			is_absolute_path_quotes(t_utils *data);
int			case_builtins_quotes(t_utils *data);
int			is_environment(t_token *root);
int			case_builtins(t_token *root);
int			extra_cases(t_token *root, t_utils *data);
int			check_brackets(t_token *root, t_utils *data);
int			check_invalid_things(t_token *root);
int			case_fd(t_token *root, t_utils *data);
int			check_is_directory(t_token *root, t_utils *data);
int			check_is_valid_fd(t_token *root, t_utils *data);
int			is_number(t_token *root);
int			case_redirect(t_token *root, t_utils *data);
int			extra_redirect_cases(t_token *root, t_utils *data);
int			heredoc_or_append(t_token *root, t_utils *data);
int			case_pipe(t_token *root, t_utils *data);
int			decrement_status(t_utils *data);
int			show_error_fd(char *message, int flag, t_utils *data, int signal);
int			free_each_split(char **split1, char **split2, int flag);
int			exist_command(t_token *root, t_utils *data);
int			check_absolute_path(t_token *root, t_utils *data);
void		get_full_path(t_token *root, int index, t_utils *data);
void		get_paths(char **envp, t_utils *data);
void		show_paths(t_utils *data);
int			free_strs_flag(char *str1, char *str2, int flag);
void		show_tokens(t_token *root);
char		*get_token(t_id id);
void		free_tokens(t_token *root);
void		add_token(t_token **root, char *str, t_id id);
t_token		*create_token(char *str, t_id id);
int			special(t_token *root, t_utils *data);
int			get_check_command(t_token *root, t_utils *data);
int			final_check(t_utils *data);
int			check_order_quotes(t_token *root);
int			case_quotes_syntax(char *quote, int marker, int *flag);
void		create_variables_order(t_token *root, int *index, int *flag);
int			special_check_quotes(t_token *root, t_utils *data);
int			how_many_quotes(t_token *root, t_utils *data);
int			ft_isalpha_special_2(char letter);
int			ft_isalpha_special(char letter);
int			check_quotes(t_token *root);
void		check_copy_new(t_utils *data);
int			godness_decision(int flag, t_utils *data);
int			pipes_case(t_token *root, t_utils *data);
int			start_case(t_token *root, t_utils *data);
int			check_local_environment(t_token *root);

//	Binary Executor

int			my_tree_my_life(t_token *root, t_utils *data);

//	Parsing
char		**convert_to_cmd(t_token **token);
void		print_split(char **split);
char		*remove_quotes(char *str);
void		*clean_array(char ***array);
int			parser(t_token **token, t_data *data);
int			is_operator(t_id id);
char		*domain_expansion(char *str, t_data *data);
char		*remove_escape(char *str);
int			find_var(char *str);
char		*expand_tilde(char *str);
int			count_var(char *str);

//	execution
char		**updateenvp(t_export **export);
int			handle_builtin(char **cmd, t_data *data);
int			minishell(t_ast **root, t_data *data);
void	call_minishell(t_ast **ast, t_data *data);
//	ast
t_ast		*create_node(char **cmd, int index);
t_ast		*add_node(t_ast *root, t_token **token);
void		print_node(t_ast *root);
void		clean_node(t_ast **root);
void		make_ast(t_token **token, t_ast **ast);

#endif
