/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:05:40 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/30 01:25:01 by tklimova         ###   ########.fr       */
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

int	ft_update_exit_code(t_parser_data *data)
{
	int	nb;

	nb = -1 * g_gb.exit_st - 1;
	if (data->cmd_line + 1 && ft_strlen(*(data->cmd_line + 1)))
	{
		nb = -1 * (int)ft_atol(*(data->cmd_line + 1)) - 1;
	}
	g_gb.exit_st = nb;
	return (g_gb.exit_st);
}

int	exit_builtin(t_parser_data *data)
{
	int		i;

	i = 1;
	if (!data || !data->text || !data->cmd_line
		|| ft_strncmp(data->text, "exit", ft_strlen(data->text)))
		return (EXIT_FAILURE);
	if (!valid_exit_arg(data->cmd_line + i))
	{
		print_error(2, "exit", "incorrect arguments");
		return (258);
	}
	else if (data->cmd_line[i] && data->cmd_line[++i])
	{
		print_error(2, "exit", "too many arguments");
		return (258);
	}
	return (ft_update_exit_code(data));
}
