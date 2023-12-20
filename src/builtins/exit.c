/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:05:40 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/20 07:59:18 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static bool	valid_exit_arg(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '-' || args[i][j] == '+')
			j++;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	exit_builtin(t_parser_data *data)
{
	int		i;

	//g_gb.exit_st = get_error();
	i = 1;
	if (!data || !data->text || !data->cmd_line
		|| ft_strncmp(data->text, "exit", ft_strlen(data->text)))
		return (EXIT_FAILURE);
	// if (data->cmd_line[i])
	// 	g_gb.exit_st = ft_atol(data->cmd_line[i]);
	if (!valid_exit_arg(data->cmd_line + i) || ft_strlen(data->cmd_line[i]))
	{
		print_error(2, "exit", "incorrect arguments");
		return (258);
	}
	else if (data->cmd_line[i] && data->cmd_line[++i])
	{
		print_error(2, "exit", "too many arguments");
		return (258);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
//	exit(0);
	return (0);
}
