/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:36:16 by plandolf          #+#    #+#             */
/*   Updated: 2023/10/09 13:24:59 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*get_path(char *text, t_data *data)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	path = get_env("PATH", data);
	paths = ft_split(path, ':');
	free(path);
	path = NULL;
	while (access(ft_strjoin(paths[i], ft_strjoin("/", text)), F_OK) == -1
		&& paths[i])
		i++;
	if (paths[i])
		path = ft_strjoin(paths[i], ft_strjoin("/", text));
	ft_free_arr(paths);
	return (path);
}

void	ft_init_env(char **envp, t_data *data)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (envp[i])
	{
		tmp = ft_strchr(envp[i], 61);
		tmp2 = ft_substr(envp[i], 0, tmp - envp[i]);
		add_env(tmp2, tmp + 1, data);
		free(tmp2);
		i++;
	}
}
