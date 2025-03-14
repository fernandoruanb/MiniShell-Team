/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:10:39 by jonas             #+#    #+#             */
/*   Updated: 2025/03/13 22:11:24 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "minishell.h"

void		create(t_data *data, char **envp);
void		execute(t_data *data);
int			destroy(t_data *data, char *message, int exit_code);
int			init_data(t_data *data, char **envp);

#endif
