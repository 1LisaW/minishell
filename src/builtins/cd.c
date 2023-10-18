/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:08:59 by plandolf          #+#    #+#             */
/*   Updated: 2023/10/16 22:18:45 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static char	*ft_home(t_data *env)
{
	char	*path;

	if (env->env_vars == NULL)
		return (NULL);
	path = get_env("HOME", env);
	if (ft_strlen(path) == 0)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		free(path);
		path = NULL;
	}
	return (path);
}

static void	ft_update_pwd(t_data *data, char *var, char *value)
{
	// int		i;
	char	*pwd;
	t_data	*tmp;

	// i = 0;
	tmp = data;
	pwd = get_env("PWD", tmp);
	if (ft_strcmp(var, "OLDPWD") == 0)
		set_env("OLDPWD", pwd, tmp);
	if (ft_strcmp(var, "PWD") == 0)
		set_env("PWD", value, tmp);
}

static int	ft_exit_cd(char **path, int exit_code)
{
	free(*path);
	*path = NULL;
	if (exit_code == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
	{
		perror("cd Error");
		return (EXIT_FAILURE);
	}
}

static int	ft_cd_home(t_data *env)
{
	char	*path;
	char	*cwd;

	cwd = NULL;
	path = ft_home(env);
	if (path == NULL)
		return (EXIT_FAILURE);
	if (chdir(path) != 0)
	{
		free(path);
		path = NULL;
		return (ft_exit_cd(&path, EXIT_FAILURE));
	}
	ft_update_pwd(env, "OLDPWD", NULL);
	cwd = getcwd(cwd, 0);
	ft_update_pwd(env, "PWD", cwd);
	free(path);
	path = NULL;
	if (get_env("PWD", env) == NULL || get_env("OLDPWD", env) == NULL)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	return (ft_exit_cd(&cwd, EXIT_SUCCESS));
}

int	cd(char **args, t_data *data)
{
	char	*cwd;
	DIR		*dir;

	if (args == NULL || data == NULL)
		return (EXIT_FAILURE);
	if (args[1] == NULL)
		return (ft_cd_home(data));
	cwd = NULL;
	dir = opendir(args[1]);
	if (dir == NULL)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	else if (closedir(dir) != 0)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	else if (chdir(args[1]) != 0)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	ft_update_pwd(data, "OLDPWD", NULL);
	cwd = getcwd(cwd, 0);
	ft_update_pwd(data, "PWD", cwd);
	if (get_env("PWD", data) == NULL
		|| get_env("OLDPWD", data) == NULL)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	return (ft_exit_cd(&cwd, EXIT_SUCCESS));
}
