/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:16:19 by jonas             #+#    #+#             */
/*   Updated: 2025/03/16 10:54:12 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

char	**convert_to_cmd(t_token **token);
void	print_array(char ***array);
void	print_split(char **split);
char	*remove_quotes(char *str);
void	*clean_array(char ***array);
int		parser(t_token **token, t_data *data);
int		find_quote(char *str);
int		is_operator(t_id id);
char	*domain_expansion(char *str, t_data *data);
char	*remove_escape(char *str);
int		find_var(char *str);
char	*expand_tilde(char *str);
char	*make_expansion(char *str, t_data *data, int i);

#endif
