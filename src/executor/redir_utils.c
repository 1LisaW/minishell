/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 06:09:10 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/22 16:53:06 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	init_exec_data(t_exec_data *exec_data)
{
	exec_data->stdin_dup = dup(STDIN_FILENO);
	exec_data->stdout_dup = dup(STDOUT_FILENO);
	exec_data->status_code = 0;
	exec_data->fd_in = STDIN_FILENO;
	exec_data->fd_out = STDOUT_FILENO;
	exec_data->was_stdinredir = 0;
	exec_data->was_stdoutredir = 0;
	exec_data->go_on = 1;
	exec_data->here_doc = NULL;
}

void	reset_std(t_exec_data *exec_data)
{
	dup2(exec_data->stdin_dup, STDIN_FILENO);
	close (exec_data->stdin_dup);
	dup2(exec_data->stdout_dup, STDOUT_FILENO);
	close(exec_data->stdout_dup);
}