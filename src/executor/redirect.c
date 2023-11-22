/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:59:55 by tklimova          #+#    #+#             */
/*   Updated: 2023/11/22 15:13:31 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	open_write_stream(t_redir_data *redir_data,
		t_exec_data *exec_data)
{
	if (exec_data->status_code)
		return ;
	if (exec_data->was_stdoutredir)
		close(exec_data->fd_out);
	exec_data->was_stdoutredir = 1;
	exec_data->fd_out = open(redir_data->text, redir_data->flags, 0755);
	if (exec_data->fd_out < 0)
	{
		exec_data->err_file = redir_data->text;
		exec_data->status_code = 1;
	}
}

void	open_stream(t_redir_data *redir_data,
		t_exec_data *exec_data, int *prev_fd)
{
	if (redir_data->is_here_doc)
	{
		here_doc(exec_data, redir_data, prev_fd);
		return ;
	}
	if (exec_data->status_code)
		return ;
	if (redir_data->std_fd == STDIN_FILENO)
	{
		close(*prev_fd);
		exec_data->was_stdinredir = 1;
		*prev_fd = open(redir_data->text, redir_data->flags);
	}
	else
	{
		open_write_stream(redir_data, exec_data);
	}
	if ((redir_data->std_fd == STDIN_FILENO) && *prev_fd < 0)
	{
		if (exec_data->was_stdoutredir)
			close(exec_data->fd_out);
		exec_data->status_code = 1;
		exec_data->err_file = redir_data->text;
	}
}

void	update_exec_data(t_parser_data *parser_node, t_exec_data *exec_data)
{
	if (!(parser_node->flags & IS_PIPE))
	{
		reset_std(exec_data, 0);
	}
	if (parser_node->flags && IS_WAIT)
		reset_std(exec_data, 1);
	if (parser_node->flags & IS_PIPE)
		exec_data->status_code = 0;
	exec_data->was_stdinredir = 0;
	exec_data->was_stdoutredir = 0;
	exec_data->fd_out = STDOUT_FILENO;
}

void	make_redirections(t_parser_data *parser_node, t_exec_data *exec_data,
			int *prev_fd)
{
	t_redir_data	*redir_data;

	if (!parser_node || !parser_node->redir_data)
		return ;
	 update_exec_data(parser_node, exec_data);
	 printf("\nmake_redirections\n");
	redir_data = parser_node->redir_data;
	while (redir_data)
	{
		open_stream(redir_data, exec_data, prev_fd);
		printf("\n STATUS_CODE REDIR %d\n", exec_data->status_code);
		redir_data = redir_data->next;
	}
	if (exec_data->status_code)
		perror(exec_data->err_file);
}

void	make_redir_without_cmd(t_parser_data *parser_node, t_exec_data *exec_data)
{
	t_redir_data	*redir_data;
	int				has_stdin_red;

	redir_data = parser_node->redir_data;
	has_stdin_red = 0;
	if (!redir_data)
		return ;
	while (!has_stdin_red && redir_data)
	{
		if (redir_data && !redir_data->std_fd)
			has_stdin_red = 1;
		redir_data = redir_data->next;
	}
	printf("make_redir_without_cmd");
	if (has_stdin_red)
	{
		parser_node->lexer_type = word;
		parser_node->text = ft_strcopy("/bin/cat");
		if (parser_node->redir_data->is_here_doc && (!parser_node->parent 
				|| !ft_strcmp(parser_node->parent->text, "|")))
			parser_node->flags = IS_WAIT;
		return ;
	}
	update_exec_data(parser_node, exec_data);
	redir_data = parser_node->redir_data;
	while (redir_data)
	{
		open_write_stream(redir_data, exec_data);
		printf("\n STATUS_CODE REDIR %d\n", exec_data->status_code);
		redir_data = redir_data->next;
	}
	if (exec_data->status_code)
		perror(exec_data->err_file);
	else
		close(exec_data->fd_out);
}
