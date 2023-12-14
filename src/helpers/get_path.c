/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:44:52 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/12 13:21:54 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static void	find_curr_path(int *i, char **paths, char *text)
{
	char	*tmp[2];

	*i = 0;
	tmp[0] = ft_strjoin("/", text);
	tmp[1] = ft_strjoin(paths[*i], tmp[0]);
	while (paths[*i]
		&& access(tmp[1], F_OK) == -1)
	{
		*i += 1;
		free(tmp[0]);
		free(tmp[1]);
		tmp[0] = ft_strjoin("/", text);
		tmp[1] = ft_strjoin(paths[*i], tmp[0]);
	}
	free(tmp[0]);
	free(tmp[1]);
}

char	*get_path(char *text, t_env *envv)
{
	char	*path;
	char	**paths;
	int		i;
	char	*tmp;

	path = NULL;
	tmp = NULL;
	path = get_env("PATH", envv);
	paths = ft_split(path, ':');
	path = NULL;
	find_curr_path(&i, paths, text);
	if (paths[i])
	{
		tmp = ft_strjoin("/", text);
		path = ft_strjoin(paths[i], tmp);
		free(tmp);
	}
	if (!paths[i])
	{
		ft_free_arr(paths);
		return (ft_strcopy(text));
	}
	ft_free_arr(paths);
	return (path);
}
