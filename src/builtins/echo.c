/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:01:14 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/20 08:00:49 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static	bool	check_option(char *s)
{
	if (!*s)
		return (false);
	if (*s == '-' && *(s + 1))
	{
		s++;
		while (*s == 'n')
			s++;
	}
	if (*s)
		return (false);
	return (true);
}

int	echo(char **cmd)
{
	bool	flg;

	cmd++;
	flg = false;
	while (*cmd && check_option(*cmd))
	{
		flg = true;
		cmd++;
	}
	while (*cmd)
	{
		ft_putstr_fd(*cmd++, 1);
		if (*cmd)
			ft_putstr_fd(" ", 1);
	}
	if (!flg)
		ft_putstr_fd("\n", 1);
	return (0);
}
