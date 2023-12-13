/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pascal <pascal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:00:47 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/14 00:46:24 by pascal           ###   ########.fr       */
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
		return (exit_with_status(1), g_gb.exit_st);
	}
	else if (printf("%s\n", cwd) != ft_strlen(cwd) + 1)
	{
		free(cwd);
		cwd = NULL;
		perror("\nPrintf error");
		return (exit_with_status(1), g_gb.exit_st);
	}
	free(cwd);
	cwd = NULL;
	return (exit_with_status(0), g_gb.exit_st);
}
