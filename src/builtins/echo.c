/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:01:14 by plandolf          #+#    #+#             */
/*   Updated: 2023/10/11 10:59:56 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	echo(char **args)
{
	int		i;
	int		n;

	i = 1;
	n = 0;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		n = 1;
		i++;
	}
	while (args[i])
	{
		if (printf("%s", args[i]) != ft_strlen(args[i]))
			return (EXIT_FAILURE);
		if (ft_strlen(args[i]) != 0 && args[i + 1] != NULL)
			if (printf(" ") != ft_strlen(" "))
				return (EXIT_FAILURE);
		i++;
	}
	if (!n)
		if (printf("\n") != ft_strlen("\n"))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
