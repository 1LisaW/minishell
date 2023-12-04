/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:36:16 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/04 11:42:05 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*get_path(char *text, t_env *envv)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	path = NULL;
	path = get_env("PATH", envv);
	paths = ft_split(path, ':');
	if (path && *path)
		free(path);
	path = NULL;
	while (paths[i]
		&& access(ft_strjoin(paths[i], ft_strjoin("/", text)), F_OK) == -1)
		i++;
	if (paths[i])
		path = ft_strjoin(paths[i], ft_strjoin("/", text));
	ft_free_arr(paths);
	return (path);
}

void	ft_init_env(char **envp, t_env **envv)
{
	int		i;
	char	*tmp_value;
	char	*tmp_var;

	i = 0;
	while (envp && envp[i])
	{
		tmp_value = ft_strchr(envp[i], 61);
		tmp_var = ft_substr(envp[i], 0, tmp_value - envp[i]);
		add_env(tmp_var, tmp_value + 1, envv);
		free(tmp_var);
		i++;
	}
}

void	exit_with_status(int exit_status)
{
	g_gb.exit_st = exit_status;
}

void	*malloc_error(int errnum)
{
	print_error(2, "malloc", strerror(errnum));
	exit_with_status(1);
	exit(1);
}

void	print_error(int n, ...)
{
	va_list	ptr;

	va_start(ptr, n);
	ft_putstr_fd("bash", 2);
	while (n--)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(va_arg(ptr, char *), 2);
	}
	ft_putstr_fd("\n", 2);
	va_end(ptr);
}
