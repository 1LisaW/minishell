/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:59:49 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/18 14:33:09 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_gb	g_gb;

static void	handle_exit(t_env **envp, t_data *data, char *cmd_buff)
{
	ft_destroy_env(envp);
	if (data->exec_data && data->exec_data->here_doc)
		close(data->exec_data->stdin_dup);
	rl_clear_history();
	ft_putendl_fd("exit", 2);
	if (cmd_buff)
		free(cmd_buff);
}

void	minishell(t_env **envp)
{
	char	*cmd_buff;
	t_data	data[1];

	init_data(data);
	data->env_vars = *envp;
	while (1) 
	{
		config_signals();
		cmd_buff = readline("minishell> ");
		if (!cmd_buff)
		{
			handle_exit(envp, data, NULL);
			break ;
		}
		if (ft_strlen(cmd_buff) > 0 && ft_strcmp(cmd_buff, "exit"))
			add_history(cmd_buff);
		if (!ft_strcmp(cmd_buff, "exit"))
		{
			handle_exit(envp, data, cmd_buff);
			break ;
		}
		lexer(data, cmd_buff);
		free(cmd_buff);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envv;

	(void)argv;
	g_gb.exit_st = 0;
	ft_init_env(envp, &envv);
	set_envv(envv);
	if (argc != 1)
		return (ft_putendl_fd("Usage: ./minishell <envp>", 2), 0);
	minishell(&envv);
	return (0);
}
