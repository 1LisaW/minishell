/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:51:15 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/11 17:50:43 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	update_flags(t_parser_data *parser_node, int *flags)
{
	if (*flags & IS_WAIT)
		*flags = 0x0;
	if (!(*flags & IS_PIPE) && parser_node->parent
		&& !ft_strcmp(parser_node->parent->text, "|"))
		*flags = IS_PIPE;
	if (parser_node->lexer_type == operator)
	{
		if (ft_strcmp(parser_node->text, "|"))
			*flags = IS_WAIT;
		else if (!parser_node->parent
			|| !ft_strcmp(parser_node->parent->text, "|"))
			*flags |= IS_WAIT;
	}
}

int	create_process(int *prev_fd, t_parser_data *parser_node, int *flags)
{
	int	fd[2];
	int	child_id;

	if (pipe(fd) == -1)
	{
		return (1);
	}
	child_id = fork();
	if (child_id == -1)
	{
		return (2);
	}
	if (child_id == 0)
	{
		close(fd[0]);
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
		if (!(*flags & IS_WAIT))
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		printf("\n EXECUTION!!\n");
		execve("/bin/cat", parser_node->cmd_line, NULL);
		exit(3);
	}
	close(*prev_fd);
	close(fd[1]);
	if (!(*flags & IS_WAIT))
		*prev_fd = fd[0];
	else
	{
		close(*prev_fd);
		while (wait(NULL) != -1)
			;
	}
	return (0);
}

void	execute_process(int *prev_fd, t_parser_data *parser_node, int *flags)
{
	update_flags(parser_node, flags);
	create_process(prev_fd, parser_node, flags);
}
