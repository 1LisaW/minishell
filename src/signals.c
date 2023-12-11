/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:29:00 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/08 10:49:51 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static void	handler(int signum)
{
	(void)signum;
	if (!g_gb.under_exec)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_gb.exit_st = 1;
	}
}

void	config_signals(void)
{
	rl_catch_signals = 0;
	if (signal(SIGINT, handler) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		return (print_error(2, "signal", strerror(errno)), exit_with_status(1));
}

void	signal_middle(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		return (print_error(2, "signal", strerror(errno)), exit_with_status(1));
}