/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:58:21 by root              #+#    #+#             */
/*   Updated: 2023/09/28 13:34:19 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <stdlib.h>

int		ft_strcmp(char *str1, char *str2);

int		ft_strlen(char *str);

void	ft_putendl_fd(char *s, int fd);

void	ft_putchar_fd(char c, int fd);

int		ft_strchr(char *str, char c);

char	*ft_strcopy(char *str);

#endif
