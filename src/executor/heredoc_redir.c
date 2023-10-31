/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:11:37 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/31 15:19:38 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	update_is_new_line(char *buffer, int *new_l, char c)
{
	if (*new_l)
		*new_l = 0;
	else
	{
		while (*buffer && *buffer != 10)
			buffer++;
		if (*buffer == 10 || c == 10)
			*new_l = 1;
	}
}

void	read_stdin(t_exec_data *exec_data, t_redir_data *redir_data,
			int *len, int *fd)
{
	char	*buffer;
	char	eol;
	int		is_new_l;

	buffer = malloc(sizeof(char) * (len[0] + 1));
	if (!buffer)
		return ;
	len[1] = read(exec_data->stdin_dup, buffer, len[0]);
	buffer[len[1]] = '\0';
	is_new_l = 1;
	while (len[1] > 0)
	{
		read(exec_data->stdin_dup, &eol, 1);
		if (!ft_strcmp(redir_data->text, buffer) && eol == 10 && is_new_l)
			break ;
		write(fd[1], buffer, len[1]);
		write(fd[1], &eol, 1);
		len[1] = read(exec_data->stdin_dup, buffer, len[0]);
		buffer[len[1]] = '\0';
		update_is_new_line(buffer, &is_new_l, eol);
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
