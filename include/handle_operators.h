/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:21:44 by jonas             #+#    #+#             */
/*   Updated: 2025/03/13 22:22:50 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_OPERATORS_H
# define HANDLE_OPERATORS_H

# include "minishell.h"

void	clean_process(t_data *data);
void	start_echo(void);
int		handle_redirect_out(char *f, t_utils *data);
int		append(char *f, t_utils *data);
int		handle_pipe_op(t_ast **root, int flag, t_data *data);
int		handle_red_in(char *f, t_utils *data);
int		heredoc(char *limiter, t_data *data, t_token **token);
int		close_descriptors(int *pipefd, int flag, t_data *data);
void	fulfil_data_fd(int *pipefd, t_data *data);
int		get_pipes(t_token *root);
int		init_pipes(t_utils *data);
void	ft_write_mode(int *pipefd, char **cmd, t_data *data);
void	ft_read_mode(char **cmd, int *pipefd, t_data *data);
void	ft_write_read_mode(int *pipefd, char **cmd, t_data *data);
void	heredoc_check_mode(t_data *data, char *limiter, int *fd);
void	check_errno(char **split1, t_utils *data, t_data *__data);
void	translate(t_data *data);
void	exec_single_cmd(t_ast **root, t_data *data);
void	single_command(t_ast **root, t_data *data);
char	*get_path(t_data *data, char **cmd);

#endif
