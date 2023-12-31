/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:59:49 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/30 01:24:02 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_gb	g_gb;

static void	handle_exit(t_env **envp, char *cmd_buff)
{
	ft_destroy_env(envp);
	rl_clear_history();
	ft_putendl_fd("exit", 2);
	if (cmd_buff)
		free(cmd_buff);
}

int	minishell(t_env **envp)
{
	char	*cmd_buff;
	t_data	data[1];

	init_data(data);
	data->env_vars = *envp;
	cmd_buff = NULL;
	while (g_gb.exit_st >= 0)
	{
		config_signals();
		cmd_buff = readline("minishell> ");
		if (!cmd_buff)
			break ;
		if (ft_strlen(cmd_buff) > 0 && ft_strcmp(cmd_buff, "exit"))
			add_history(cmd_buff);
		lexer(data, cmd_buff);
		free(cmd_buff);
		cmd_buff = NULL;
	}
	handle_exit(envp, cmd_buff);
	g_gb.exit_st = -1 * (g_gb.exit_st + 1);
	return (g_gb.exit_st);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envv;

	(void)argv;
	g_gb.exit_st = 0;
	ft_init_env(envp, &envv);
	set_envv(envv);
	set_envp(envp);
	if (argc != 1)
		return (ft_putendl_fd("Usage: ./minishell <envp>", 2), 0);
	return (minishell(&envv));
}
