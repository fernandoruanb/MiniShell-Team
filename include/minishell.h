/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:09:17 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/13 22:25:01 by jonas            ###   ########.fr       */
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
# include <stdbool.h>
# include <readline/history.h>

//	Our libs
# include "structs.h"
# include "colours.h"
# include "utils.h"
# include "token.h"
# include "main.h"
# include "prompt.h"
# include "builtin.h"
# include "lexer.h"
# include "syntax_check.h"
# include "parsing.h"
# include "execution.h"
# include "handle_operators.h"
# include "ast.h"
# include "handle_signals.h"

//	Binary Executor
int			my_tree_my_life(t_token *root, t_utils *data);

#endif
