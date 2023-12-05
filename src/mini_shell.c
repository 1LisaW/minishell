/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:59:49 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/05 14:54:30 by tklimova         ###   ########.fr       */
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
	parser_data->cmd_line = malloc(sizeof(char **)*100);
	// parser_data->text = malloc(sizeof(char **)*100);
	char **args = malloc(sizeof(char **)*100);
	char **args_echo = malloc(sizeof(char **)*100);

	parser_data->text = ft_strcopy("echo");
	parser_data->cmd_line[0] = "hello";
	args[1] = "/nfs/homes/plandolf/curriculum/";
	args_echo[0] = "echo";
	args_echo[1] = "-n";
	args_echo[2] = "hello";
	init_data(data);
	data->env_vars = *envp;
	while (1)
	{
		config_signals();
		cmd_buff = readline("minishell> ");
		if (!cmd_buff)
		{
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
		//testing builtin commands TO REMOVE
		if (!ft_strcmp(cmd_buff, "env"))
			print_env(*envp);
		if (!ft_strcmp(cmd_buff, "pwd"))
			pwd();
		if (!ft_strcmp(cmd_buff, "cd"))
			cd(args, *envp);
		if (!ft_strcmp(cmd_buff, "echo"))
			echo(parser_data);
		// test ends here
			// echo(args_echo);
		//end testing builtin commands
		lexer(data, cmd_buff);
		free(cmd_buff);
	}
	free(args_echo);
	free(args);
	free(parser_data->cmd_line);
	free(parser_data->text);
	free(parser_data);
}

// static void test_modify_cmd(const char *input, const char *expected, t_env *data) {
//     char test_string[1024];  // Large enough for our test cases
//     strcpy(test_string, input);
//     modify_cmd(test_string, data);
//     if (strcmp(test_string, expected) != 0) {
//         printf("Failed for input \"%s\". Expected \"%s\" but got \"%s\".\n", input, expected, test_string);
//     } else {
//         printf("Passed for input \"%s\".\n", input);
//     }
// }

int	main(int argc, char **argv, char **envp)
{
	char	*tmpstr;
	char	*s;
	t_env	*envv;

	tmpstr = malloc(sizeof(char **)*1000);
	// data = malloc(sizeof(t_data));
	(void)argv;
	g_gb.exit_st = 0;
// 	data->env_vars = NULL;
	ft_init_env(envp, &envv);
	if (argc != 1)
		return (ft_putendl_fd("Usage: ./minishell <envp>", 2), 0);
	//testing modify_cmd TO REMOVE
//	tmpstr = ft_strcopy("\"echo $ARG\"");
//test_modify_cmd(tmpstr, "echo ho", envv);
//free(tmpstr);
//test_modify_cmd("echo '$ARG'", "echo '$ARG'", envv);
//test_modify_cmd("echo $ARG", "echo ho", envv);
s = ft_strcopy("\"\"\'\'echo \"$ARG\"");
modify_cmd(tmpstr, s, envv);
printf("%s\n", tmpstr);
tmpstr = new_cmd(tmpstr, NULL);
printf("%s\n", tmpstr);
free(tmpstr);
//test_modify_cmd("e'c$ARGa'", "e'c$ARGa'", envv);

// tmpstr = ft_strcopy("\'\'ec\"$ARG\"a");
// test_modify_cmd(tmpstr, "e'c$ARGa'", envv);
// test_modify_cmd("e'c$ARGa'", "e'c$ARGa'", envv);
// free(tmpstr);

//char test_string[1024];  // Large enough for our test cases
//strcpy(test_string, "ec$ARG'a");
//modify_cmd(test_string, envv);
//printf("%s\n", test_string);

//end testing modify_cmd
// <<<<<<< C-013
// 	minishell(data->env_vars);
// =======
	minishell(&envv);
	return (0);
}
