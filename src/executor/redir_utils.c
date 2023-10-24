/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 06:09:10 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/24 15:25:35 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	init_exec_data(t_exec_data *exec_data)
{
	exec_data->stdin_dup = dup(STDIN_FILENO);
	exec_data->stdout_dup = dup(STDOUT_FILENO);
	exec_data->status_code = 0;
	exec_data->fd_out = STDOUT_FILENO;
	exec_data->was_stdinredir = 0;
	exec_data->was_stdoutredir = 0;
	exec_data->go_on = 1;
}

void	reset_std(t_exec_data *exec_data, int fd)
{
	if (fd)
	{
		if (dup2(exec_data->stdout_dup, STDOUT_FILENO) == -1)
			return ;
		close(exec_data->stdout_dup);
		exec_data->stdout_dup = dup(STDOUT_FILENO);
	}
	else
	{
		if (dup2(exec_data->stdin_dup, STDIN_FILENO) == -1)
			return ;
		close(exec_data->stdin_dup);
		exec_data->stdin_dup = dup(STDIN_FILENO);
	}
}

void clear_exec_data(t_exec_data *exec_data, t_data *data)
{
	data->status_code = exec_data->status_code;
	dup2(exec_data->stdin_dup, STDIN_FILENO);
	dup2(exec_data->stdout_dup, STDOUT_FILENO);
	close(exec_data->stdin_dup);
	close(exec_data->stdout_dup);
}

void	read_stdin(t_exec_data *exec_data, t_redir_data *redir_data,
			int *len, int *fd)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (len[0] + 2));
	if (!buffer)
		return ;
	len[1] = read(exec_data->stdin_dup, buffer, len[0]);
	buffer[len[1]] = '\0';
	while (ft_strcmp(redir_data->text, buffer) && len[1] > 0)
	{
		write(fd[1], buffer, len[1]);
		len[1] = read(exec_data->stdin_dup, buffer, len[0]);
		buffer[len[1]] = '\0';
	}
	close(fd[1]);
	free(buffer);
}

void	here_doc(t_exec_data *exec_data, t_redir_data *redir_data, int *prev_fd)
{
	int		len[2];
	int		fd[2];

	if (!redir_data->is_here_doc)
		return ;
	len[0] = ft_strlen(redir_data->text);
	if (pipe(fd) == -1)
		return ;
	read_stdin(exec_data, redir_data, len, fd);
	if (!exec_data->status_code)
		*prev_fd = fd[0];
	else
		close(fd[0]);
}
