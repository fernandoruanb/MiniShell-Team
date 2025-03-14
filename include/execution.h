/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:17:22 by jonas             #+#    #+#             */
/*   Updated: 2025/03/13 22:21:08 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

int		minishell(t_ast **root, t_data *data);
int		handle_builtin(char **cmd, t_data *data);
char	**updateenvp(t_export **exp);
char	*find_path(char *cmd, char **env, t_data *data);
int		manage_redir(t_token **token, t_data *data);
void	restore_redirect(int *original, t_data *data);
int		*save_origin(t_data *data);
void	make_redir(int fd, int fd2);
void	destroy_fd(int **fd);
void	exec_pipe(t_ast **root, t_data *data);
void	*call_clean(t_data *data, int flag);
int		isbuiltin(char *cmd);

#endif
