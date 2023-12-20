/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:00:47 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/20 09:13:32 by tklimova         ###   ########.fr       */
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
		return (1);
	}
	else if (printf("%s\n", cwd) != ft_strlen(cwd) + 1)
	{
		free(cwd);
		cwd = NULL;
		perror(cwd);
		perror("\nPrintf error");
		return (1);
	}
	free(cwd);
	cwd = NULL;
	return (0);
}
