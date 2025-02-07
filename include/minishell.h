/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:08:19 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/07 11:30:21 by jopereir         ###   ########.fr       */
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

typedef struct s_ast
{
	char			*cmd;
	char			**argv;

	struct s_ast	*parent;
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
	char	**envp;
	char	*path;

	pid_t	pid;
	int		exit_status;
}	t_prompt;

typedef struct s_data
{
	t_prompt	*prompt;
	t_token		*token;	
}	t_data;

//	0-utils.c
void	*clear_split(char **str);
char	*ft_strndup(char *str, int n);

//	1-token
t_token	*token_create(char *str, int n, int index, t_id id);
t_token	*token_add(t_token *token, t_token *new, t_token *prev);
void	token_clean(t_token *token);
/*
	temporaria, apagar antes de mandar
*/
void	token_print(t_token *token);

//	main
void	create(t_data *data, char **envp);
void	execute(t_data *data);
int		destroy(t_data *data, char *message, int exit_code);
int		init_data(t_data *data, char **envp);

//	prompt
void	exec_cmd(t_prompt *prompt);
int		child(t_prompt *prompt);
void	display_prompt(t_data *data);

//	built_in/
void	ft_cd(char *input);
void	ft_echo(t_prompt *prompt);
char	*enviroment_var(char *cmd, int exit_status);
int		ft_exit(char *name, t_data *data, char *exit_status);

//	lexer
t_token	*lexer(char *str, char **envp);
int		handle_bracket(char *str, t_token **token, t_lex *lex);
int		handle_and(char *str, t_token **token, t_lex *lex);
int		handle_less(char *str, t_token **token, t_lex *lex);
int		handle_great(char *str, t_token **token, t_lex *lex);
int		handle_word(char *str, t_token **token, t_lex *lex);
int		is_word(unsigned char c);
int		is_quote(unsigned char c);
int		handle_quote(char *str, t_token **token, t_lex *lex);
int		handle_pipe(char *str, t_token **token, t_lex *lex);

#endif
