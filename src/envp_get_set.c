/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_get_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:38:56 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/18 13:25:59 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static char	**_get_envp(char *envp[], bool reset)
{
	static char	**static_envp = NULL;

	if (envp == NULL && !reset)
		return (static_envp);
	if (reset)
	{
		static_envp = NULL;
		return (NULL);
	}
	static_envp = envp;
	return (static_envp);
}

void	set_envp(char *envp[])
{
	_get_envp(envp, false);
}

char	**get_envp(void)
{
	return (_get_envp(NULL, false));
}

void	reset_envp(void)
{
	_get_envp(NULL, true);
}
