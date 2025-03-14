/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:08:19 by jonas             #+#    #+#             */
/*   Updated: 2025/03/13 22:09:08 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h" 

void		*clear_split(char **str);
char		*ft_strndup(char *str, int n);
int			my_free_my_life(void *s1, void *s2, void *s3, int __return__);
int			splitlen(char **split);

#endif
