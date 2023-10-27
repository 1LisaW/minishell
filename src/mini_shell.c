/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:59:49 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/27 17:03:24 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

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

void	minishell(t_env *envp)
{
	char	*cmd_buff;
	t_data	data[1];
	char	**args = malloc(sizeof(char **) * 100000000);
	char	**args_echo = malloc(sizeof(char **) * 100000000);

	args[1] = "/nfs/homes/plandolf/curriculum/";
	args_echo[0] = "echo";
	args_echo[1] = "-n";
	args_echo[2] = "hello";
	init_data(data);
	data->env_vars = envp;
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
			rl_clear_history();
			break ;
		}
		//testing builtin commands TO REMOVE
		if (!ft_strcmp(cmd_buff, "env"))
			print_env(envp);
		if (!ft_strcmp(cmd_buff, "pwd"))
			pwd();
		if (!ft_strcmp(cmd_buff, "cd"))
			cd(args, envp);
		if (!ft_strcmp(cmd_buff, "echo"))
			echo(args_echo);
		//end testing builtin commands
		lexer(data, cmd_buff);
		free(cmd_buff);
	}
}

static void test_modify_cmd(const char *input, const char *expected, t_env *data) {
    char test_string[1024];  // Large enough for our test cases
    strcpy(test_string, input);
    modify_cmd(test_string, data);
    if (strcmp(test_string, expected) != 0) {
        printf("Failed for input \"%s\". Expected \"%s\" but got \"%s\".\n", input, expected, test_string);
    } else {
        printf("Passed for input \"%s\".\n", input);
    }
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*envv;

	(void)argv;
	envv = NULL;
	ft_init_env(envp, &envv);
	if (argc != 1)
		return (ft_putendl_fd("Usage: ./minishell <envp>", 2), 0);
	//testing modify_cmd TO REMOVE
test_modify_cmd("echo $ARG", "echo ho", envv);
test_modify_cmd("echo '$ARG'", "echo '$ARG'", envv);
test_modify_cmd("echo \"$ARG\"", "echo \"ho\"", envv);
test_modify_cmd("e'c$ARGa'", "e'c$ARGa'", envv);
char test_string[1024];  // Large enough for our test cases
strcpy(test_string, "ec$ARG'a");
modify_cmd(test_string, envv);
printf("%s\n", test_string);

//end testing modify_cmd
	minishell(envv);
	return (0);
}
