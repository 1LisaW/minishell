/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:08:59 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/20 02:13:08 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static char	*ft_home(t_env *env)
{
	char	*path;

	if (env == NULL)
		return (NULL);
	path = get_env_value("HOME", env);
	if (ft_strlen(path) == 0)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		free(path);
		path = NULL;
	}
	return (path);
}

static void	ft_update_pwd(t_env *env, char *var, char *value)
{
	char	*pwd;
	t_env	*tmp;

	tmp = env;
	pwd = get_env_value("PWD", tmp);
	if (ft_strcmp(var, "OLDPWD") == 0)
		set_env("OLDPWD", pwd, &tmp);
	if (ft_strcmp(var, "PWD") == 0)
		set_env("PWD", value, &tmp);
}

static int	ft_exit_cd(char **path, int exit_code)
{
	free(*path);
	*path = NULL;
	if (exit_code == EXIT_SUCCESS)
		return (exit_with_status(0), g_gb.exit_st);
	else
	{
		perror("cd Error");
		return (exit_with_status(1), g_gb.exit_st);
	}
}

static int	ft_cd_home(t_env *env)
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
	if (get_env_value("PWD", env) == NULL
		|| get_env_value("OLDPWD", env) == NULL)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	return (ft_exit_cd(&cwd, EXIT_SUCCESS));
}

int	cd(char **args)
{
	char	*cwd;
	DIR		*dir;
	t_env	*env;

	env = get_envv();
	if (args == NULL || env == NULL)
		return (EXIT_FAILURE);
	if (args[1] == NULL)
		return (ft_cd_home(env));
	cwd = NULL;
	dir = opendir(args[1]);
	if (dir == NULL)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	else if (closedir(dir) != 0)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	else if (chdir(args[1]) != 0)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	ft_update_pwd(env, "OLDPWD", NULL);
	cwd = getcwd(cwd, 0);
	ft_update_pwd(env, "PWD", cwd);
	if (get_env_value("PWD", env) == NULL
		|| get_env_value("OLDPWD", env) == NULL)
		return (ft_exit_cd(&cwd, EXIT_FAILURE));
	return (ft_exit_cd(&cwd, EXIT_SUCCESS));
}
