/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_cmd_helpers2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:26:26 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/04 11:58:27 by plandolf         ###   ########.fr       */
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
	exit_with_status(258);
	return (-1);
}

void	expand_and_modify(void)
{
}
