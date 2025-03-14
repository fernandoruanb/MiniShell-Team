/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:12:39 by jonas             #+#    #+#             */
/*   Updated: 2025/03/13 22:13:29 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

void		ft_cd(char *input);
int			ft_pwd(t_data *data);
int			ft_echo(char **str);
int			ft_env(t_data *data);
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

#endif
