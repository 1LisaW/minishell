/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:00:47 by plandolf          #+#    #+#             */
/*   Updated: 2023/10/05 12:10:16 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
	else if (printf("%s\n", cwd) != ft_strlen(cwd) + 1)
	{
		free(cwd);
		cwd = NULL;
		perror("\nPrintf error");
		return (EXIT_FAILURE);
	}
	free(cwd);
	cwd = NULL;
	return (EXIT_SUCCESS);
}
