/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:59:55 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/18 18:29:19 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	save_std(t_exec_data *exec_data)
{
	if (exec_data->was_stdinredir && exec_data->was_stdoutredir)
		return ;
	if (!exec_data->was_stdinredir)
	{
		exec_data->stdin_dup = dup(STDIN_FILENO);
		exec_data->was_stdinredir = 1;
	}
	else if (!exec_data->was_stdoutredir)
	{
		exec_data->stdout_dup = dup(STDOUT_FILENO);
		exec_data->was_stdoutredir = 1;
	}
}

void	clear_savedstd(t_exec_data *exec_data)
{
	if (!exec_data->was_stdinredir && !exec_data->was_stdoutredir)
		return;
	if (exec_data->was_stdinredir)
	{
		dup2(STDIN_FILENO, exec_data->stdin_dup);
		close(exec_data->stdin_dup);
		exec_data->was_stdinredir = 0;
	}
	else if (exec_data->was_stdoutredir)
	{
		dup2(STDOUT_FILENO, exec_data->stdout_dup);
		close(exec_data->stdout_dup);
		exec_data->was_stdoutredir = 0;
	}
}

void	open_stream(int *fd, t_redir_data *redir_data,
		t_exec_data *exec_data)
{
	if (!redir_data->std_fd && redir_data->is_here_doc)
	{
		if (exec_data->was_stdinredir)
			fd[0] = dup(exec_data->stdin_dup);
		else
			fd[0] = dup(STDIN_FILENO);
		exec_data->here_doc = redir_data->text;
		return ;
	}
	if (!redir_data->std_fd)
	{
		fd[0] = open(redir_data->text, redir_data->flags);
		exec_data->here_doc = NULL;
	}
	else
		fd[1] = open(redir_data->text, redir_data->flags, 0755);
	if (fd[redir_data->std_fd] < 0)
	{
		clear_savedstd(exec_data);
		exec_data->status_code = 1;
	}
	else
	{
		save_std(exec_data);
		dup2(fd[redir_data->std_fd], redir_data->std_fd);
		close(fd[redir_data->std_fd]);
	}
}

void	make_redirections(t_parser_data *parser_node, t_exec_data *exec_data)
{
	int				fd[2];
	t_redir_data	*redir_data;

	fd[0] = 0;
	fd[1] = 1;
	if (parser_node->parent && ft_strcmp(parser_node->parent->text, "|"))
		clear_savedstd(exec_data);
	if (!parser_node || !parser_node->redir_data)
		return ;
	redir_data = parser_node->redir_data;
	while (redir_data && !exec_data->status_code)
	{
		open_stream(fd, redir_data, exec_data);
		printf("\n STATUS_CODE REDIR %d\n", exec_data->status_code);
		redir_data = redir_data->next;
	}
}

