/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:30:06 by plandolf          #+#    #+#             */
/*   Updated: 2023/10/09 13:24:55 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"
#include <string.h>

char	*get_env(char *text, t_data *data)
{
	t_env	*tmp;

	tmp = data->env_vars;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, text))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("\0");
}

void	set_env(char *var, char *value, t_data *data)
{
	t_env	*tmp;

	tmp = data->env_vars;
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
	add_env(var, value, data);
}

void	unset_var(char *var, t_data *data)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = data->env_vars;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, var))
		{
			if (prev)
				prev->next = tmp->next;
			else
				data->env_vars = tmp->next;
			free(tmp->var);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	add_env(char *var, char *value, t_data *data)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	tmp->var = ft_strdup(var);
	tmp->value = ft_strdup(value);
	tmp->next = data->env_vars;
	data->env_vars = tmp;
}
