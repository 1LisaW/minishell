/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:51:15 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/09 13:04:49 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"


int	child_process(int *prev_fd, int *fd, t_parser_data *parser_node)
{
	if (dup2(*prev_fd, STDIN_FILENO) == -1)
		return (3);
	close(*prev_fd);
	if (!(parser_node->flags & IS_WAIT))
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}

	execve(parser_node->text, parser_node->cmd_line, NULL);
	write(1, "\n has error \n", 10);
	return (4);
}

int	create_process(int *prev_fd, t_parser_data *parser_node)
{
	int	fd[2];
	int	child_id;

	if (!(parser_node->flags & IS_WAIT) && pipe(fd) == -1)
		return (1);
	child_id = fork();
	if (child_id == -1)
		return (2);
	if (child_id == 0)
		child_process(prev_fd, fd, parser_node);
	close(*prev_fd);
	if (!(parser_node->flags & IS_WAIT))
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	else
		close(*prev_fd);
	return (0);
}

void	execute_process(int *prev_fd, t_parser_data *parser_node)
{
	if (parser_node->lexer_type == word)
		create_process(prev_fd, parser_node);
	if (parser_node->flags & IS_WAIT)
	{
		printf("\n Waiting for execution: %s\n", parser_node->text);
		while (wait(NULL) != -1)
			;
	}
}
