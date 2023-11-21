/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:05:40 by plandolf          #+#    #+#             */
/*   Updated: 2023/10/26 14:31:28 by plandolf         ###   ########.fr       */
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
	long	exit_code;
	int		i;

	exit_code = get_error();
	i = 1;
	if (!data || !data->text || !data->cmd_line 
		|| ft_strncmp(data->text, "exit", ft_strlen(data->text)))
		return (EXIT_FAILURE);
	if (data->cmd_line[i])
		exit_code = ft_atol(data->cmd_line[i]);
	if (!valid_exit_arg(data->cmd_line + i) || ft_strlen(data->cmd_line[i]))
	{
		ft_putendl_fd("exit: invalid argument", STDERR_FILENO);
		exit_code = 255;
	}
	else if (data->cmd_line[i] && data->cmd_line[++i])
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(exit_code);
	return (exit_code);
}
