/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:36:16 by plandolf          #+#    #+#             */
/*   Updated: 2023/09/28 10:47:39 by plandolf         ###   ########.fr       */
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
	while (access(ft_strjoin(paths[i], text), F_OK) == -1 && paths[i])
		i++;
	if (paths[i])
		path = ft_strjoin(paths[i], text);
	free_split(paths);
	return (path);
}
