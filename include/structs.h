/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:05:11 by jonas             #+#    #+#             */
/*   Updated: 2025/03/13 22:06:26 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

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
	char				*input;
	char				*path;
	unsigned int		exit_status;
}	t_prompt;

typedef struct s_utils
{
	char		*temp;
	char		*path;
	char		*line_heredoc;
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
	int			rl_flag;
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
	char		*filename;
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

typedef struct s_clean_flags
{
	bool	should_clean;
	bool	shoud_restore;
}	t_flags;

typedef struct s_data
{
	t_prompt	*prompt;
	t_token		*token;
	t_utils		utils;
	t_ast		*root;
	t_export	*export_vars;
	t_localvar	*local_vars;
	t_flags		flags;

	char		**original_envp;
	int			*fd;
	int			is_pipe;
	char		**envp;
}	t_data;

#endif
