/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:29:27 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/30 15:39:25 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINI_H
# define MINI_H 

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct s_data
{
	char	*line;
	char	**envp;
	char	*oldpwd;
	char	*newpwd;
	int		file_stdin;
	int		file_stdout;
	int		file_stderr;
	int		cmds;
	int		args;
	int		pipes;
	int		status;
	int		redirect_in;
	int		redirect_out;
	int		redirect_out_append;
	int		redirect_in_heredoc;
	int		redirect_in_triple;
	int		redirect_out_triple;
	struct t_tokens	*tokens;
}	t_data;

typedef enum e_id
{
	PIPE,
	CMD,
	ARG,
	BRACKET,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_OUT_APPEND,
	REDIRECT_IN_HEREDOC,
	LOGICAL_AND_OPERATOR,
	LOGICAL_OR_OPERATOR,
}	t_id;

typedef struct s_token
{
	char	*value;
	t_id	type;
	int	index;
	char	**args;
	struct s_token	*next;
	struct s_token	*prev;
}	t_tokens;

void	execute(t_data *data, char **envp);
int		builtins(t_data *data);
void	ft_cd(t_data *data);
void	ft_env(t_data *data);
void	ft_echo(t_data *data);
void	free_shell(t_data *data);
int		is_only_spaces(t_data *data);

#endif /* MINISHELL_H */
