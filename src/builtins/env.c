/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:54:20 by pascal            #+#    #+#             */
/*   Updated: 2023/12/20 07:19:47 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	env(char **argv)
{
	t_env	*envv;

	envv = get_envv();
	if (envv == NULL || envv->var == NULL)
		return (exit_with_status(1), g_gb.exit_st);
	if (argv != NULL && argv[1] != NULL)
	{
		if (access(argv[1], F_OK) == 0)
		{
			ft_putstr_fd("permission denied\n", 2);
			return (126);
		}
		ft_putstr_fd("command not found\n", 2);
		return (127);
	}
	while (envv)
	{
		ft_putstr_fd(envv->var, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(envv->value, 1);
		envv = envv->next;
	}
	return (0);
}
