/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:17:22 by jonas             #+#    #+#             */
/*   Updated: 2025/03/21 00:35:58 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

int		minishell(t_ast **root, t_data *data);
int		handle_builtin(char **cmd, t_data *data);
char	**updateenvp(t_export **exp);
char	*find_path(char *cmd, char **env, t_data *data);
int		manage_redir(t_ast **root, t_token **token, t_data *data);
void	restore_redirect(int *original, t_data *data);
int		*save_origin(t_data *data);
void	make_redir(int fd, int fd2);
void	destroy_fd(int **fd);
void	*call_clean(t_data *data, int flag);
int		isbuiltin(char *cmd);
int		call_echo(t_data *data, char **cmd);
int		switch_redir(t_token **token, t_data *data);
void	aplly_redirect(int fd, t_id id);
char	*find_fd(t_token **token);
t_ast	*find_cmd(t_ast **root);
int		exec_pipe(t_ast **root, t_data *data);
char	*get_str(char *str);
int		redir_out(char *name, t_id id, t_data *data);
int		redir_in(char *name, t_id id, t_token **token, t_data *data);
t_ast	*find_cmd2(t_ast **root);

#endif
