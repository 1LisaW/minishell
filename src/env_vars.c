/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:30:06 by plandolf          #+#    #+#             */
/*   Updated: 2023/09/28 10:35:23 by plandolf         ###   ########.fr       */
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

void	ft_init_env(char **envp, t_data *data)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (envp[i])
	{
		tmp = ft_strchr(envp[i], 61);
		tmp2 = ft_substr(envp[i], 0, tmp - envp[i]);
		add_env(tmp2, tmp + 1, data);
		free(tmp2);
		i++;
	}
}
