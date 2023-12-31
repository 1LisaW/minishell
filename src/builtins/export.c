/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:01:35 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/20 10:01:40 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static	bool	export_help(char *s)
{
	ssize_t	l;
	char	*save;

	l = 0;
	save = s;
	while (identifier_front(*save))
	{
		l++;
		save++;
	}
	while (is_identifier(*save))
		save++;
	if (!l || (!(*save == '+' && *(save + 1) == '=') && *save != '=' && *save))
		return (print_error(3, "export", s, "not a valid identifier"),
			false);
	return (export_var(s, *save), true);
}

static	void	sort_env(t_env *env)
{
	t_env	*save;
	char	*s;

	while (env)
	{
		save = env->next;
		while (save)
		{
			if (strcmp(env->var, save->var) > 0)
			{
				s = env->var;
				env->var = save->var;
				save->var = s;
				s = env->value;
				env->value = save->value;
				save->value = s;
			}
			save = save->next;
		}
		env = env->next;
	}
}

static	t_env	*copy_env(void)
{
	t_env	*env;
	t_env	*ret;

	env = get_envv();
	ret = NULL;
	while (env)
	{
		add_env(env->var, env->value, &ret);
		env = env->next;
	}
	return (ret);
}

static	void	print_env(void)
{
	t_env	*env;
	t_env	*save;

	env = copy_env();
	sort_env(env);
	save = env;
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->var, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\"\n", 1);
		env = env->next;
	}
	free_env(save);
}

int	export(char **cmd)
{
	if (!cmd[1])
		print_env();
	else
	{
		while (*++cmd)
			if (!export_help(*cmd))
				return (0);
	}
	return (0);
}
