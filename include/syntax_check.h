/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:15:01 by jonas             #+#    #+#             */
/*   Updated: 2025/03/13 22:15:48 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_CHECK_H
# define SYNTAX_CHECK_H

# include "minishell.h"

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

#endif
