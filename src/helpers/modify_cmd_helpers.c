/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_cmd_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:18:41 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/11 21:42:13 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*expand_var(char *s, int *i, t_env *env)
{
	int		keep;
	char	*var;
	char	*str;

	keep = *i;
	if (s[keep] && s[keep] == '?')
		return ((*i)++, ft_itoa(g_gb.exit_st));
	while (s[keep] && is_identifier(s[keep]))
		keep++;
	keep -= *i;
	str = ft_substr(s, *i, keep);
	var = get_env(str, env);
	*i += keep;
	if (!var || !*var)
		return (free(str), str = NULL, NULL);
	return (free(str), str = NULL, var);
}

bool	is_identifier(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

char	*new_cmd(char *s, bool *flg)
{
	char	*new;
	char	*save;
	ssize_t	l;
	char	kp;

	new = malloc(sizeof(char) * (calc_len(s) + 1));
	if (!new)
		return (malloc_error(errno));
	l = 0;
	save = s;
	while (*s)
	{
		if (*s == 34 || *s == 39)
		{
			kp = *s++;
			should_expnd(flg);
			while (*s != kp && *s)
				new[l++] = *s++;
			s++;
			continue ;
		}
		new[l++] = *s++;
	}
	return (new[l] = '\0', free(save), new);
}

void	eliminate_quotes_phase(char **args)
{
	char	*s;

	while (*args)
	{
		s = new_cmd(*args, NULL);
		*args = s;
		args++;
	}
}

void	should_expnd(bool *flg)
{
	if (flg)
		*flg = 0;
}
