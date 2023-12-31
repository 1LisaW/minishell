/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_cmd_helpers2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:26:26 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/28 23:57:00 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	calc_len(char *s)
{
	int		l;
	int		save;
	char	kp;

	l = 0;
	while (*s)
	{
		if (*s == 34 || *s == 39)
		{
			kp = *s;
			save = check_next_quote(++s, kp);
			s += save + 1;
			l += save;
			continue ;
		}
		s++;
		l++;
	}
	return (l);
}

int	check_next_quote(char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			return (i);
		i++;
		s++;
	}
	ft_putendl_fd("syntax error: unclosed quotes", 1);
	return (-1);
}
