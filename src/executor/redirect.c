/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:59:55 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/23 18:05:51 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	here_doc(t_exec_data *exec_data, t_redir_data *redir_data, int *prev_fd)
{
	char	*buffer;
	int		len[2];
	int		fd[2];

	if (!redir_data->is_here_doc)
		return;
	len[0] = ft_strlen(redir_data->text);
	if (pipe(fd) == -1)
		return;
	buffer = malloc(sizeof(char) * (len[0] + 2));
	if (!buffer)
		return;
	len[1] = read(exec_data->stdin_dup, buffer, len[0]);
	buffer[len[1]] = '\0';
	while (ft_strcmp(redir_data->text, buffer) && len[1] > 0)
	{
		write(fd[1], buffer, len[1]);
		len[1] = read(exec_data->stdin_dup, buffer, len[0]);
		buffer[len[1]] = '\0';
	}
	close(fd[1]);
	if (!exec_data->status_code)
		*prev_fd = fd[0];
		// dup2(fd[0], STDIN_FILENO);
	else
		close(fd[0]);
	free(buffer);
}

void	open_write_stream(t_redir_data *redir_data,
		t_exec_data *exec_data)
{
		if (exec_data->status_code)
			return;
		if (exec_data->was_stdoutredir)
			close(exec_data->fd_out);
		exec_data->was_stdoutredir = 1;
		exec_data->fd_out = open(redir_data->text, redir_data->flags, 0755);
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
	if (!redir_data->std_fd)
	{
		//if (exec_data->was_stdinredir)
		close(*prev_fd);
		exec_data->was_stdinredir = 1;
		*prev_fd = open(redir_data->text, redir_data->flags);
	}
	else
	{
		open_write_stream(redir_data, exec_data);
	}
	if (!redir_data->std_fd && *prev_fd < 0)
	{
		exec_data->status_code = 1;
	}
	// else if (!redir_data->std_fd)
	// 	close(fd[redir_data->std_fd]);
}

void update_exec_data(t_parser_data *parser_node, t_exec_data *exec_data)
{
	if (!(parser_node->flags & IS_PIPE))
	{
		restart_std(exec_data, 0);
		restart_std(exec_data, 1);
	}
	else
		exec_data->status_code = 0;
	exec_data->was_stdinredir = 0;
	exec_data->was_stdoutredir = 0;
}

void	make_redirections(t_parser_data *parser_node, t_exec_data *exec_data,
			int *prev_fd)
{
	t_redir_data	*redir_data;

	if (!parser_node || !parser_node->redir_data)
		return ;
	redir_data = parser_node->redir_data;
	while (redir_data && !exec_data->status_code)
	{
		update_exec_data(parser_node, exec_data);
		open_stream(redir_data, exec_data, prev_fd);
		printf("\n STATUS_CODE REDIR %d\n", exec_data->status_code);
		redir_data = redir_data->next;
	}
}
