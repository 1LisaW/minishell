/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:59:49 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/11 11:00:51 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	print_env(t_data *envp)
{
	t_env	*tmp;

	tmp = envp->env_vars;
	while (tmp)
	{
		ft_putstr_fd(tmp->var, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(tmp->value, 1);
		tmp = tmp->next;
	}
}

void	minishell(t_data *envp)
{
	char	*cmd_buff;
	t_data	data[1];
	char **args = malloc(sizeof(char **)*100000000);
	char **args_echo = malloc(sizeof(char **)*100000000);

	args[1] = "/nfs/homes/plandolf/curriculum/";
	args_echo[0] = "echo";
	args_echo[1] = "-n";
	args_echo[2] = "hello";
	init_data(data);
	while (1)
	{
		config_signals();
		cmd_buff = readline("minishell> ");
		if (!cmd_buff)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		if (ft_strlen(cmd_buff) > 0)
			add_history(cmd_buff);
		if (!ft_strcmp(cmd_buff, "exit"))
		{
			if (cmd_buff)
				free(cmd_buff);
			destroy_data(data);
			rl_clear_history();
			break ;
		}
		if (!ft_strcmp(cmd_buff, "env"))
			print_env(envp);
		if (!ft_strcmp(cmd_buff, "pwd"))
			pwd();
		if (!ft_strcmp(cmd_buff, "cd"))
			cd(args, envp);
		if (!ft_strcmp(cmd_buff, "echo"))
			echo(args_echo);
		lexer(data, cmd_buff);
		free(cmd_buff);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*envv;

	(void)argv;
	envv = (t_data *)malloc(sizeof(t_data));
	ft_init_env(envp, envv);
	if (argc != 1)
		return (ft_putendl_fd("Usage: ./minishell <envp>", 2), 0);
	minishell(envv);
	return (0);
}
