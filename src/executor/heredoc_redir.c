/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:11:37 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/28 19:57:31 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static void	sigint_here_doc_handler(int sig)
{
	int	pipefd[2];

	(void) sig;
	g_gb.exit_st = 130;
	if (pipe(pipefd) < 0)
		perror("Pipe: ");
	dup2(pipefd[0], STDIN_FILENO);
	write(pipefd[1], "\n\n", 2);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	read_str(char *buffer, char *delimiter, int fd_out,
			t_exec_data *exec_data)
{
	while (ft_strcmp(buffer, delimiter))
	{
		if (g_gb.exit_st)
		{
			exec_data->ctrl_c = 1;
			break ;
		}
		write(fd_out, buffer, ft_strlen(buffer));
		write(fd_out, "\n", 1);
		if (g_gb.exit_st)
			break ;
		signal(SIGINT, sigint_here_doc_handler);
		buffer = readline("heredoc>");
		signal(SIGINT, handle_cmd_signal);
	}
}

void	read_stdin(t_exec_data *exec_data, t_redir_data *redir_data,
			int *fd)
{
	char	*buffer;

	buffer = NULL;
	g_gb.exit_st = 0;
	read_str(buffer, redir_data->text, fd[1], exec_data);
	close(fd[1]);
	free(buffer);
	if (g_gb.exit_st)
		exec_data->status_code = g_gb.exit_st;
}

void	here_doc(t_exec_data *exec_data, t_redir_data *redir_data, int *prev_fd)
{
	int		fd[2];

	if (!redir_data->is_here_doc)
		return ;
	if (pipe(fd) == -1)
		return ;
	read_stdin(exec_data, redir_data, fd);
	if (!exec_data->status_code)
		*prev_fd = fd[0];
	else
		close(fd[0]);
}
