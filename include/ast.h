/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:23:05 by jonas             #+#    #+#             */
/*   Updated: 2025/03/13 22:23:59 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"

void	clean_node(t_ast **root);
void	print_node(t_ast *root);
t_ast	*add_node(t_ast *root, t_token **token);
t_ast	*create_node(char **cmd, int index, t_id id);
void	make_ast(t_token **token, t_ast **ast, t_data *data);
void	handle_redir(t_token **token, t_ast **ast);
int		isredir(t_id id);

#endif
