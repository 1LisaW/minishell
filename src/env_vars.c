/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:30:06 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/06 13:57:17 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"
#include <string.h>

char	*get_env(char *text, t_env *envv)
{
	t_env	*tmp;

	tmp = envv;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, text))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("\0");
}

void	set_env(char *var, char *value, t_env **envv)
{
	t_env	*tmp;

	tmp = *envv;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, var))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	add_env(var, value, envv);
}

void	unset_var(char *var, t_env **envv)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *envv;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, var))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*envv = tmp->next;
			free(tmp->var);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	add_env(char *var, char *value, t_env **envv)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = malloc(sizeof(t_env));
	tmp->var = ft_strdup(var);
	tmp->value = ft_strdup(value);
	tmp->next = (*envv);
	*envv = tmp;
}
