/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 06:09:10 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/11 21:01:18 by tklimova         ###   ########.fr       */
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

void	clear_exec_data(t_exec_data *exec_data, t_data *data)
{
	data->status_code = exec_data->status_code;
	dup2(exec_data->stdin_dup, STDIN_FILENO);
	dup2(exec_data->stdout_dup, STDOUT_FILENO);
	close(exec_data->stdin_dup);
	close(exec_data->stdout_dup);
}

void	change_redir_data_without_cmd(t_parser_data *parser_node)
{
	parser_node->lexer_type = word;
	parser_node->text = ft_strcopy("/bin/cat");
	if (parser_node->redir_data->is_here_doc && (!parser_node->parent
			|| !ft_strcmp(parser_node->parent->text, "|")))
		parser_node->flags = IS_WAIT;
}
