/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:11:37 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/12 23:58:38 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	update_heredoc_params(int *pos, int *is_new_line, char curr_char)
{
	*pos = 0;
	if (curr_char == '\n')
		*is_new_line = 1;
	else
		*is_new_line = 0;
}

void	write_in_stdout(int fd_out, char *buffer, int *pos, int *is_new_line)
{
	write(fd_out, buffer, *pos + 1);
	update_heredoc_params(pos, is_new_line, buffer[*pos]);
}

void	read_str(char *buffer, char *delimiter, int fd_out,
			t_exec_data *exec_data)
{
	int	pos;
	int	rb;
	int	is_new_line;
	int	len;

	len = ft_strlen(delimiter);
	update_heredoc_params(&pos, &is_new_line, 10);
	rb = 1;
	while (pos < len && rb)
	{
		printf("%i\n", g_gb.exit_st);
		buffer[pos] = '\0';
		rb = read(exec_data->stdin_dup, buffer + pos, 1);
		if (buffer[pos] != delimiter[pos] || buffer[pos] == 10)
			write_in_stdout(fd_out, buffer, &pos, &is_new_line);
		else
			pos++;
		if (pos == len && rb && is_new_line)
		{
			rb = read(exec_data->stdin_dup, buffer + pos, 1);
			if (buffer[pos] == 10)
				break ;
			write_in_stdout(fd_out, buffer, &pos, &is_new_line);
		}
	}
}

void	read_stdin(t_exec_data *exec_data, t_redir_data *redir_data,
			int *len, int *fd)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (len[0] + 1));
	if (!buffer)
		return ;
	read_str(buffer, redir_data->text, fd[1], exec_data);
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
