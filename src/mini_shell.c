/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:59:49 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/11 09:43:25 by plandolf         ###   ########.fr       */
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
	t_parser_data	*parser_data = NULL;
	
	parser_data = malloc(sizeof(t_parser_data));
	init_data(data);
	data->env_vars = *envp;
	while (1)
	{
		config_signals();
		cmd_buff = readline("minishell> ");
		if (!cmd_buff)
		{
			ft_putendl_fd("exit", 2);
			free_env(envp);
			break ;
		}
		if (ft_strlen(cmd_buff) > 0 && ft_strcmp(cmd_buff, "exit"))
			add_history(cmd_buff);
		if (!ft_strcmp(cmd_buff, "exit"))
		{
			if (cmd_buff)
				free(cmd_buff);
			free_env(envp);
			rl_clear_history();
			break ;
		}
		g_gb.under_exec = 1;
		lexer(data, cmd_buff);
		free(cmd_buff);
		g_gb.under_exec = 0;
	}
	//ft_destroy_env(envp);
	free(parser_data->cmd_line);
	free(parser_data->text);
	free(parser_data);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envv;

	(void)argv;
	g_gb.exit_st = 0;
	g_gb.under_exec = 0;
	ft_init_env(envp, &envv);
	if (argc != 1)
		return (ft_putendl_fd("Usage: ./minishell <envp>", 2), 0);
	// modify_cmd(tmpstr, s, envv);
	// printf("%s\n", tmpstr);
	// tmpstr = new_cmd(tmpstr, NULL);
	// printf("%s\n", tmpstr);
	minishell(&envv);
	return (0);
}
