/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:01:14 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/11 11:31:39 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	echo(t_parser_data *data)
{
	int		i;
	int		n;

	i = 1;
	n = 0;
	if (data->cmd_line[1] && ft_strcmp(data->cmd_line[1], "-n") == 0)
	{
		n = 1;
		i++;
	}
	while (data->cmd_line[i])
	{
		if (printf("%s", data->cmd_line[i]) != ft_strlen(data->cmd_line[i]))
			return (EXIT_FAILURE);
		if (ft_strlen(data->cmd_line[i]) != 0 && data->cmd_line[i + 1] != NULL)
			if (printf(" ") != ft_strlen(" "))
				return (EXIT_FAILURE);
		i++;
	}
	if (!n)
		if (printf("\n") != ft_strlen("\n"))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
