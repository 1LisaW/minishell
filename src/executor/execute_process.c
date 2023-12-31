/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:51:15 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/31 14:54:58 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	run_buildin(t_exec_data *exec_data, t_parser_data *parser_node,
		int opt)
{
	int	status_code;

	if (is_builtin(parser_node->text) != 1)
		return (0);
	if ((parser_node->flags & IS_PIPE) == opt && exec_data->was_stdoutredir)
	{
		dup2(exec_data->fd_out, STDOUT_FILENO);
		if (!exec_data->status_code && exec_data->fd_out != -1)
			close(exec_data->fd_out);
	}
	if ((parser_node->flags & IS_PIPE) == opt)
	{
		status_code = exec_builtins(parser_node);
		if (parser_node->flags & IS_WAIT)
		{
			exec_data->status_code = status_code;
			ft_set_gb_status_code(exec_data);
		}
		return (1);
	}
	return (0);
}

void	handle_fd(int *prev_fd)
{
	if (dup2(*prev_fd, STDIN_FILENO) == -1)
		exit(4);
	if (*prev_fd != -1)
		close(*prev_fd);
}

void	child_process(int *prev_fd, int *fd, t_parser_data *parser_node,
			t_exec_data *exec_data)
{
	t_env	*envv;
	char	**envp;

	envv = get_envv();
	envp = env_list_to_array(envv);
	handle_fd(prev_fd);
	close(fd[0]);
	if (!(parser_node->flags & IS_WAIT))
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (exec_data->was_stdoutredir)
	{
		dup2(exec_data->fd_out, STDOUT_FILENO);
		if (!exec_data->status_code && exec_data->fd_out != -1)
			close(exec_data->fd_out);
	}
	if (exec_data->status_code && (exec_data->was_stdinredir
			|| exec_data->was_stdoutredir || exec_data->here_doc))
		exit(exec_data->status_code);
	if (run_buildin(exec_data, parser_node, 0x2))
		exit (exec_data->status_code);
	execve(parser_node->text, parser_node->cmd_line, envp);
	exit(ft_response_bad_execve(parser_node->text));
}

int	parent_process(int *prev_fd, t_exec_data *exec_data,
			int *fd, t_parser_data *parser_node)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	close(fd[1]);
	if (exec_data->was_stdoutredir && !exec_data->status_code)
		close(exec_data->fd_out);
	if (!(parser_node->flags & IS_WAIT))
	{
		*prev_fd = fd[0];
		return (0);
	}
	else
		*prev_fd = dup(STDIN_FILENO);
	return (1);
}

int	create_process(int *prev_fd, t_parser_data *parser_node,
		t_exec_data *exec_data)
{
	int	fd[2];
	int	child_id;

	handle_cmd_signals();
	make_redirections(parser_node, exec_data, prev_fd);
	if (run_buildin(exec_data, parser_node, 0x0))
		return (0);
	if (pipe(fd) == -1)
		return (1);
	child_id = fork();
	if (child_id == -1)
		return (2);
	if (child_id == 0)
		child_process(prev_fd, fd, parser_node, exec_data);
	if (parent_process(prev_fd, exec_data, fd, parser_node))
	{
		reset_std(exec_data, 1);
		dup2(fd[0], STDOUT_FILENO);
		close(fd[0]);
		waitpid(child_id, &exec_data->status_code, 0);
		ft_set_gb_status_code(exec_data);
	}
	config_signals();
	return (0);
}
