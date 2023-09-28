/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:29:00 by plandolf          #+#    #+#             */
/*   Updated: 2023/09/28 11:32:12 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

//to close childs we will probably need it later
void	child_signals(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		exit(130);
	}
}

void	dismiss_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	config_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &dismiss_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
