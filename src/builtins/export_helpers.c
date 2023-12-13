/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pascal <pascal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:39:39 by pascal            #+#    #+#             */
/*   Updated: 2023/12/14 00:32:57 by pascal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static	char	*eliminate_plus(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(s));
	if (!ret)
		return (malloc_error(errno));
	while (*s)
	{
		if (*s == '+')
			s++;
		ret[i++] = *s++;
	}
	ret[i] = '\0';
	return (ret);
}

static	void	env_hlp(t_env *trav, char *s, ssize_t index, char c)
{
	char	*tmp;
	char	*save;

	if (c == '+')
	{
		s = eliminate_plus(s);
		tmp = ft_substr(s, index + 1, ft_strlen(s) - index);
		save = ft_strjoin(trav->value, tmp);
		(free(trav->value), free(tmp), free(s), trav->value = save);
	}
	else
	{
		save = ft_substr(s, index + 1, ft_strlen(s) - index);
		free(trav->value);
		trav->value = save;
	}
	save = ft_strjoin(trav->var, "=");
	free(trav->var);
	free(save);
}

static	bool	access_env(char *var, char *s, ssize_t index, char c)
{
	t_env	*trav;

	trav = get_envv();
	while (trav)
	{
		if (!ft_memcmp(var, trav->var, ft_strlen(var) + 1))
		{
			if (c)
				env_hlp(trav, s, index, c);
			else
				(free(trav->var), trav->var = NULL);
			return (trav->var = var, true);
		}
		trav = trav->next;
	}
	return (false);
}

static	void	export_var_help(char *s, char *var, char c,
		ssize_t index)
{
	t_env	*trav;

	trav = get_envv();
	if (c == '=')
		(add_env(var, ft_substr(s, index + 1, ft_strlen(s) - index), &trav));
	else if (c == '+')
	{
		s = eliminate_plus(s);
		(add_env(var, ft_substr(s, index + 1, ft_strlen(s) - index), &trav));
	}
	else
		(add_env(var, "", &trav));
	free(var);
}

void	export_var(char *s, char c)
{
	ssize_t	index;
	char	*var;

	index = 0;
	if (c)
	{
		index = find_c(s, c);
		var = ft_substr(s, 0, index);
	}
	else
		var = ft_strdup(s);
	if (access_env(var, s, index, c))
		;
	else
		export_var_help(s, var, c, index);
}
