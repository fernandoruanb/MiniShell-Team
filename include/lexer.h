/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:13:46 by jonas             #+#    #+#             */
/*   Updated: 2025/03/20 16:36:29 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

t_token	*lexer(char *str, char **envp);
int		is_cmd(char *str, t_lex *lex);
int		handle_bracket(char *str, t_token **token, t_lex *lex);
int		handle_and(char *str, t_token **token, t_lex *lex);
int		handle_less(char *str, t_token **token, t_lex *lex);
int		handle_great(char *str, t_token **token, t_lex *lex);
int		handle_word(char *str, t_token **token, t_lex *lex);
int		is_word(unsigned char c, int flag);
int		is_quote(unsigned char c);
int		handle_pipe(char *str, t_token **token, t_lex *lex);
int		quote_close(char *str, int k);
void	get_label(t_lex *lex, t_token **token);
int		error_message(char *message, int __return__, t_token **token);
int		handle_fd(char *str);
void	handle_empty(t_lex *lex, int *i, char *str);

#endif
