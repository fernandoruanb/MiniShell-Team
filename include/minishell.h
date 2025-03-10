/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:09:17 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/10 16:40:28 by jopereir         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <readline/history.h>

# define BLUE "\033[0;36m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RED "\033[38;5;214m"
# define RESET	"\033[0m"

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

typedef struct s_ast	t_ast;

typedef struct s_ast
{
	char	**cmd;
	int		index;
	t_id	id;

	t_ast	*left;
	t_ast	*right;
}	t_ast;

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
	char	*path;
	int		exit_status;
}	t_prompt;

typedef struct s_utils
{
	char		*temp;
	char		*path;
	char		**paths;
	char		**envp;
	int			**pipes_fd;
	int			status;
	int			redirects;
	int			files;
	int			pid;
	int			commands;
	int			pipes;
	int			temp_fd;
	int			fd_backup;
	int			exec_status;
	int			exit_status;
	int			simple_quotes;
	int			double_quotes;
	char		*newpwd;
	char		*oldpwd;
	char		*line;
	char		*copy_new;
	int			args;
	int			pids[9000];
	int			index;
	int			brackets_c;
	int			num_of_processes;
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

typedef struct s_var
{
	char			*name;
	char			*value;

	struct s_var	*next;
	struct s_var	*prev;
}	t_localvar;

typedef struct s_data
{
	t_prompt	*prompt;
	t_token		*token;
	t_utils		utils;
	t_ast		*root;
	t_export	*export_vars;
	t_localvar	*local_vars;

	char		**original_envp;
	int			*fd;
	int			is_pipe;
	char		**envp;
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
void		clear_everything(t_data *data, int flag);
void		display_prompt(t_data *data);
void		analysis(t_data *data);

//	built_in/
void		ft_cd(char *input);
int			ft_pwd(t_data *data);
int			ft_echo(char **str);
int			ft_env(t_data *data);
char		*enviroment_var(char *cmd, int exit_status);
void		ft_exit(t_data *data, char *exit_status);
int			valid_name(char c, int flag);
int			ft_export(char *input, t_export **var);
t_export	*search_var(t_export **var, char *name);
void		ft_unset(t_export **var, t_localvar **local, char *name);
void		export_clean(t_export **var);
void		export_init(char **envp, t_export **var);
int			ft_localvar(char *input, t_localvar **var);
void		clean_locals(t_localvar	*var);
t_localvar	*init_local(void);
char		*get_var(char *input);
int			export_print(t_export **var);
t_export	*export_last(t_export **var);
void		locals_print(t_localvar **var);
t_localvar	*search_locals(t_localvar **var, char *name);

//	lexer
t_token		*lexer(char *str, char **envp);
int			is_cmd(char *str, t_lex *lex);
int			handle_bracket(char *str, t_token **token, t_lex *lex);
int			handle_and(char *str, t_token **token, t_lex *lex);
int			handle_less(char *str, t_token **token, t_lex *lex);
int			handle_great(char *str, t_token **token, t_lex *lex);
int			handle_word(char *str, t_token **token, t_lex *lex);
int			is_word(unsigned char c, int flag);
int			is_quote(unsigned char c);
int			handle_pipe(char *str, t_token **token, t_lex *lex);
int			quote_close(char *str, int k);
void		get_label(t_lex *lex);
int			error_message(char *message, int __return__, t_token **token);
int			handle_fd(char *str);

// syntax checker
void		init_utils(t_utils *data, char **envp);
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
// void		clean_program(t_utils *data);
// int			check_syntax(t_token *root, char **envp, t_utils *data);
// int			get_command(t_token *root, t_utils *data);
// int			final_case(t_token *root, t_utils *data);
// int			check_invalid_brackets_position(t_utils *data);
// int			case_arg(t_token *root, t_utils *data);
// int			case_limiter(t_token *root, t_utils *data);
// int			case_command(t_token *root, t_utils *data);
// int			is_insider_quotes(t_token *root, t_utils *data);
// int			test_all_paths(t_utils *data);
// int			is_absolute_path_quotes(t_utils *data);
// int			case_builtins_quotes(t_utils *data);
// int			is_environment(t_token *root);
// int			case_builtins(t_token *root);
// int			extra_cases(t_token *root, t_utils *data);
// int			check_brackets(t_token *root, t_utils *data);
// int			check_invalid_things(t_token *root);
// int			case_fd(t_token *root, t_utils *data);
// int			check_is_directory(t_token *root, t_utils *data);
// int			check_is_valid_fd(t_token *root, t_utils *data);
// int			is_number(t_token *root);
// int			case_redirect(t_token *root, t_utils *data);
// int			extra_redirect_cases(t_token *root, t_utils *data);
// int			heredoc_or_append(t_token *root, t_utils *data);
// int			case_pipe(t_token *root, t_utils *data);
// int			decrement_status(t_utils *data);
// int			show_error_fd(char *message, int flag, t_utils *data, int signal);
// int			free_each_split(char **split1, char **split2, int flag);
// int			exist_command(t_token *root, t_utils *data);
// int			check_absolute_path(t_token *root, t_utils *data);
// void		get_full_path(t_token *root, int index, t_utils *data);
// void		get_paths(char **envp, t_utils *data);
// void		show_paths(t_utils *data);
// int			free_strs_flag(char *str1, char *str2, int flag);
// void		show_tokens(t_token *root);
// char		*get_token(t_id id);
// void		free_tokens(t_token *root);
// void		add_token(t_token **root, char *str, t_id id);
// t_token		*create_token(char *str, t_id id);
// int			special(t_token *root, t_utils *data);
// int			get_check_command(t_token *root, t_utils *data);
// int			final_check(t_utils *data);
// int			check_order_quotes(t_token *root);
// int			case_quotes_syntax(char *quote, int marker, int *flag);
// void		create_variables_order(t_token *root, int *index, int *flag);
// int			special_check_quotes(t_token *root, t_utils *data);
// int			how_many_quotes(t_token *root, t_utils *data);
// int			ft_isalpha_special_2(char letter);
// int			ft_isalpha_special(char letter);
// int			check_quotes(t_token *root);
// void		check_copy_new(t_utils *data);
int			godness_decision(int flag, t_utils *data);
int			pipes_case(t_token *root, t_utils *data);
int			start_case(t_token *root, t_utils *data);
int			check_local_environment(t_token *root);

//	Binary Executor
int			my_tree_my_life(t_token *root, t_utils *data);

//	Parsing
char		**convert_to_cmd(t_token **token);
void		print_array(char ***array);
void		print_split(char **split);
char		*remove_quotes(char *str);
void		*clean_array(char ***array);
int			parser(t_token **token, t_data *data);
int			find_quote(char *str);
int			is_operator(t_id id);
char		*domain_expansion(char *str, t_data *data);
char		*remove_escape(char *str);
int			find_var(char *str);
char		*expand_tilde(char *str);

//	execution
int			minishell(t_ast **root, t_data *data);
int			handle_builtin(char **cmd, t_data *data);
char		**updateenvp(t_export **export);
char		*find_path(char *cmd, char **env, t_data *data);
int			manage_redir(t_token **token, t_data *data);
void		restore_redirect(int *original);
int			*save_origin(void);
void		make_redir(int fd, int fd2);
void		destroy_fd(int *fd);
void		exec_pipe(t_ast **root, t_data *data);
void		*call_clean(t_data *data);

// HANDLE_OPERATORS

int			handle_redirect_out(char *f, t_utils *data);
int			append(char *f, t_utils *data);
int			handle_pipe_op(t_ast **root, int flag, t_data *data);
int			handle_red_in(char *f, t_utils *data);
void		operator_and(char *cmd1, char *cmd2, t_data *data);
void		operator_or(char *cmd1, char *cmd2, t_data *data);
int			heredoc(char *limiter, t_utils *data);
void		operator_and(char *cmd1, char *cmd2, t_data *data);
void		operator_or(char *cmd1, char *cmd2, t_data *data);
int			close_descriptors(int *pipefd, int flag, t_data *data);
void		fulfil_data_fd(int *pipefd, t_data *data);
int			get_pipes(t_token *root);
int			init_pipes(t_utils *data);
void		ft_write_mode(int *pipefd, char **cmd, t_data *data);
void		ft_read_mode(char **cmd, int *pipefd, t_data *data);
void		ft_write_read_mode(int *pipefd, char **cmd, t_data *data);
void		heredoc_check_mode(char *line, char *limiter, int fd);
void		check_errno(char **split1, t_utils *data, t_data *__data);
void		translate(t_data *data);
void		exec_single_cmd(t_ast **root, t_data *data);
void		single_command(t_ast **root, t_data *data);

//	ast
void		clean_node(t_ast **root);
void		print_node(t_ast *root);
t_ast		*add_node(t_ast *root, t_token **token);
t_ast		*create_node(char **cmd, int index, t_id id);
void		make_ast(t_token **token, t_ast **ast, t_data *data);
void		handle_redir(t_token **token, t_ast **ast);
int			isredir(t_id id);

// HANDLE_SIGNALS

void		handle_prompt_signal(void);
void		heredoc_signal(void);
void		handle_command_signal(void);

#endif
