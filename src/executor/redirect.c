/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:59:55 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/22 18:18:00 by tklimova         ###   ########.fr       */
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
		return ;
	if (exec_data->was_stdinredir)
	{
		dup2(STDIN_FILENO, exec_data->stdin_dup);
		// close(exec_data->stdin_dup);
		exec_data->was_stdinredir = 0;
	}
	else if (exec_data->was_stdoutredir)
	{
		dup2(STDOUT_FILENO, exec_data->stdout_dup);
		// close(exec_data->stdout_dup);
		exec_data->was_stdoutredir = 0;
	}
}


void	here_doc(t_exec_data *exec_data, t_redir_data *redir_data)
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
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buffer);
}

void	open_stream(int *fd, t_redir_data *redir_data,
		t_exec_data *exec_data)
{
	if (redir_data->is_here_doc)
	{
		here_doc(exec_data, redir_data);
		// if (exec_data->was_stdinredir)
		// 	fd[0] = dup(exec_data->stdin_dup);
		// else
		// 	fd[0] = dup(STDIN_FILENO);
		// exec_data->here_doc = redir_data->text;
		return ;
	}
	if (exec_data->status_code)
		return ;
	if (!redir_data->std_fd)
	{
		fd[0] = open(redir_data->text, redir_data->flags);
		// exec_data->here_doc = NULL;
	}
	else
		fd[1] = open(redir_data->text, redir_data->flags, 0755);
	if (fd[redir_data->std_fd] < 0)
	{
		// clear_savedstd(exec_data);
		exec_data->status_code = 1;
		// return ;
	}
	// save_std(exec_data);
	dup2(fd[redir_data->std_fd], redir_data->std_fd);
	if (fd[redir_data->std_fd] > 0)
		close(fd[redir_data->std_fd]);
}

// void	here_doc(t_exec_data *exec_data)
// {
// 	char	*limiter;
// 	char	*buffer;
// 	int		len[2];
// 	int		fd[2];

// 	if (!exec_data->here_doc)
// 		return;
// 	limiter = exec_data->here_doc;
// 	len[0] = ft_strlen(limiter);
// 	buffer = malloc(sizeof(char) * (len[0] + 1));
// 	if (!buffer)
// 		return;
// 	if (pipe(fd) == -1)
// 	{
// 		free(buffer);
// 		return;
// 	}
// 	len[1] = read(STDIN_FILENO, buffer, len[0]);
// 	buffer[len[1]] = '\0';
// 	while(ft_strcmp(limiter, buffer) && len[1] > 0)
// 	{
// 		write(fd[1], buffer, len[1]);
// 		len[1] = read(STDIN_FILENO, buffer, len[0]);
// 		buffer[len[1]] = '\0';
// 	}
// 	close(fd[1]);
// 	dup2(fd[0], STDIN_FILENO);
// 	close(fd[0]);
// 	free(buffer);
// }

void	make_redirections(t_parser_data *parser_node, t_exec_data *exec_data,
			int *prev_fd, int *fd)
{
	// int				fd[2];
	t_redir_data	*redir_data;

	// fd[0] = STDIN_FILENO;
	// fd[1] = STDOUT_FILENO;

	}
	// if (parser_node->parent && ft_strcmp(parser_node->parent->text, "|"))
	// 	clear_savedstd(exec_data);
	if (!parser_node || !parser_node->redir_data)
		return ;
	redir_data = parser_node->redir_data;
	while (redir_data && !exec_data->status_code)
	{
		open_stream(fd, redir_data, exec_data);
		printf("\n STATUS_CODE REDIR %d\n", exec_data->status_code);
		redir_data = redir_data->next;
	}
	// here_doc(exec_data);
}
