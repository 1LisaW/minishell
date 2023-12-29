/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:15:20 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/29 21:17:28 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	command_not_found(char *cmd)
{
	char	**cmds;

	cmds = NULL;
	cmds = malloc(3 * sizeof(char *));
	cmds[0] = ft_strjoin("command-not-found", NULL);
	cmds[1] = ft_strjoin(cmd, NULL);
	cmds[2] = NULL;
	execve("/usr/lib/command-not-found", cmds, NULL);
}

void	bind_current_path_to_cmd(t_parser_data *parser_node, t_env *env)
{
	char	*cmd_with_path;

	cmd_with_path = NULL;
	cmd_with_path = get_path(parser_node->text, env);
	free(parser_node->text);
	parser_node->text = ft_strcopy(cmd_with_path);
	free(parser_node->cmd_line[0]);
	parser_node->cmd_line[0] = ft_strcopy(cmd_with_path);
	free(cmd_with_path);
}

void	ft_set_gb_status_code(t_exec_data *exec_data)
{
	if (g_gb.exit_st == 404)
		g_gb.exit_st = 130;
	else if (exec_data->ctrl_c)
		g_gb.exit_st = 130;
	else
		g_gb.exit_st = WEXITSTATUS(exec_data->status_code);
	if (g_gb.exit_st == 4)
		g_gb.exit_st = 1;
}
