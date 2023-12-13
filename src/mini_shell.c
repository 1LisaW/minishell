/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pascal <pascal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:59:49 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/14 00:39:02 by pascal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_gb	g_gb;

void	print_env(t_env *envv)
{
	t_env	*tmp;

	tmp = envv;
	while (tmp)
	{
		ft_putstr_fd(tmp->var, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(tmp->value, 1);
		tmp = tmp->next;
	}
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
			ft_destroy_env(envp);
			rl_clear_history();
			ft_putendl_fd("exit", 2);
			break ;
		}
		if (ft_strlen(cmd_buff) > 0 && ft_strcmp(cmd_buff, "exit"))
			add_history(cmd_buff);
		if (!ft_strcmp(cmd_buff, "exit"))
		{
			if (cmd_buff)
				free(cmd_buff);
			ft_destroy_env(envp);
			rl_clear_history();
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
