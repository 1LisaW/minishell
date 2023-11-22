/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 06:09:10 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/31 15:18:57 by tklimova         ###   ########.fr       */
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
