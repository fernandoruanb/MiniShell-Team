/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:08:19 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/24 13:23:37 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
#include <readline/history.h>

typedef struct s_prompt
{
	char	*input;
	char	**cmdset;
	char	**envp;
	char	*path;

	pid_t	pid;
}	t_prompt;

typedef struct s_data
{
	t_prompt	*prompt;
}	t_data;

//	0-utils.c
void	*clear_split(char **str);

//	main/2-events.c
void	create(t_data *data, char **envp);
void	execute(t_data *data);
void	destroy(t_data *data, char *message, int exit_code);

//	prompt/3-display_prompt.c
void	display_prompt(t_prompt *prompt);

//	main/3-init.c
int		init_data(t_data *data, char **envp);

//	prompt/5-exec_cmd.c
void	exec_cmd(t_prompt *prompt);

#endif
