/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:51:15 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/18 18:31:48 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	run_buildin(t_exec_data *exec_data, t_parser_data *parser_node, int opt)
{
	int	status_code;

	if ((parser_node->flags & IS_PIPE) == opt
		&& !ft_strcmp(parser_node->text, "/bin/pwd"))
	{
		//if redir -> run dup for redirs
		//if !status code run
		printf("We should run buildin command!!! flags:%d\n", parser_node->flags);
		// replace 0 on result of exec buildin command
		status_code = 0;
		if (parser_node->flags & IS_WAIT)
			exec_data->status_code = status_code;
		//it redir clode all fd and redup original stds
		return (1);
	}
	return (0);
}

void	child_process(int *prev_fd, int *fd, t_parser_data *parser_node, t_exec_data *exec_data)
{
	if (dup2(*prev_fd, STDIN_FILENO) == -1)
		return ;
	close(*prev_fd);
	if (!(parser_node->flags & IS_WAIT))
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	make_redirections(parser_node, exec_data);
	if (exec_data->status_code)
		exit(1);
	if (run_buildin(exec_data, parser_node, 0x2))
		return ;
	execve(parser_node->text, parser_node->cmd_line, NULL);
	execve("/usr/lib/command-not-found", parser_node->cmd_line, NULL);
	//write(1, "\n has error \n", 10);
	// exit(EXIT_FAILURE);
}

int	create_process(int *prev_fd, t_parser_data *parser_node, t_exec_data *exec_data)
{
	int	fd[2];
	int	child_id;

	if (run_buildin(exec_data ,parser_node, 0x0))
		return (0);
	if (!(parser_node->flags & IS_WAIT) && pipe(fd) == -1)
		return (1);
	child_id = fork();
	if (child_id == -1)
		return (2);
	if (child_id == 0)
		child_process(prev_fd, fd, parser_node, exec_data);
	close(*prev_fd);
	if (!(parser_node->flags & IS_WAIT))
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	else
	{
		waitpid(child_id, &exec_data->status_code, 0);
		if (WIFEXITED(exec_data->status_code))
			printf("\n WIFEXITED STATUS of %s is: %d, %d\n", parser_node->text, WEXITSTATUS(exec_data->status_code), exec_data->status_code);
		close(*prev_fd);
	}
	return (0);
}

void	check_prolong(t_parser_data *parser_node, t_exec_data *exec_data)
{
	if (!ft_strcmp(parser_node->text, "&&") && exec_data->status_code)
		exec_data->go_on = 0;
	if (!ft_strcmp(parser_node->text, "||") && !exec_data->status_code)
		exec_data->go_on = 0;
}

void	execute_process(int *prev_fd, t_parser_data *parser_node, t_exec_data *exec_data)
{

	if (parser_node->lexer_type == operator)
		return check_prolong(parser_node, exec_data);
	if (parser_node->lexer_type == word)
		create_process(prev_fd, parser_node, exec_data);
	if (parser_node->flags & IS_WAIT)
	{
		printf("\n Waiting for execution: %s\n", parser_node->text);
		while (wait(NULL) != -1)
			;
		clear_savedstd(exec_data);
		// if (WIFEXITED(status))
			// printf("\n STATUS of %s is: %d\n", parser_node->text, WEXITSTATUS(status));
	}
}
