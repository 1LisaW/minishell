/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:30:06 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/18 14:45:39 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*get_env_value(char *text, t_env *envv)
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

static t_env	*create_new_node(char *var, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		malloc_error(errno);
		return (NULL);
	}
	new_node->var = ft_strdup(var);
	new_node->value = ft_strdup(value);
	if (!(new_node->var) || !(new_node->value))
	{
		free(new_node->var);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

void	add_env(char *var, char *value, t_env **envv)
{
	t_env	*new_node;
	t_env	*last;

	if (!envv)
		return ;
	new_node = create_new_node(var, value);
	if (!new_node)
		return ;
	if (!*envv)
		*envv = new_node;
	else
	{
		last = *envv;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}
