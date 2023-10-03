/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:58:21 by root              #+#    #+#             */
/*   Updated: 2023/10/03 15:04:16 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>

typedef struct	s_split_next
{
	size_t start;
	size_t length;
}				t_split_next;

int		ft_strcmp(char *str1, char *str2);

int		ft_strlen(char *str);

void	ft_putendl_fd(char *s, int fd);

void	ft_putchar_fd(char c, int fd);

char	*ft_strchr(char *str, int c);

char	*ft_strdup(char *s);

void	ft_putstr_fd(char *s, int fd);

char	*ft_substr(char *s, unsigned int start, int len);

char	**ft_split(char *s, char c);

char	*ft_strjoin(char *s1, char *s2);

void	ft_free_arr(char **arr);

#endif
