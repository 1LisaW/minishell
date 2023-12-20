/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:01:53 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/20 10:01:25 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static	void	delete_node(t_env *node, int keep)
{
	t_env	*save;

	if (!keep)
	{
		save = get_envv();
		save = save->next;
	}
	else
	{
		save = node->next;
		node->next = node->next->next;
	}
	free(save->var);
	free(save->value);
	(free(save), save = NULL);
}

static	bool	valid_identifier(char *s)
{
	int	l;

	l = 0;
	while (identifier_front(*s))
	{
		s++;
		l++;
	}
	while (is_identifier(*s))
		s++;
	if (!l || (!(*s == '+' && *(s + 1) == '=') && *s != '=' && *s))
		return (print_error(3, "unset", s, "not a valid identifier"),
			false);
	return (true);
}

bool	identifier_front(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

int	unset(char **cmd)
{
	t_env	*env;
	t_env	*save;
	int		keep;

	while (*++cmd)
	{
		if (!valid_identifier(*cmd))
			continue ;
		g_gb.exit_st = 0;
		env = get_envv();
		keep = 0;
		while (env)
		{
			if (!ft_memcmp(*cmd, env->var, ft_strlen(*cmd) + 1))
			{
				delete_node(save, keep);
				break ;
			}
			save = env;
			env = env->next;
			keep++;
		}
	}
	return (0);
}

void	free_env(t_env *env)
{
	t_env	*keep;

	while (env)
	{
		keep = env;
		env = env->next;
		(free(keep), keep = NULL);
	}
	exit_with_status(0);
}
