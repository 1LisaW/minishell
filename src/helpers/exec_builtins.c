/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:52:33 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/20 07:41:58 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "export") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

int	exec_builtins(t_parser_data *token)
{
	if (ft_strcmp(token->text, "echo") == 0)
		return (echo(token->cmd_line));
	if (ft_strcmp(token->text, "export") == 0)
		return (export(token->cmd_line));
	if (ft_strcmp(token->text, "env") == 0)
		return (env(token->cmd_line));
	if (ft_strcmp(token->text, "cd") == 0)
		return (cd(token->cmd_line));
	if (ft_strcmp(token->text, "unset") == 0)
		return (unset(token->cmd_line));
	if (ft_strcmp(token->text, "pwd") == 0)
		return (pwd());
	if (ft_strcmp(token->text, "exit") == 0)
		return (exit_builtin(token));
	return (EXIT_FAILURE);
}
