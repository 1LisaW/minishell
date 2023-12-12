/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:42:42 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/06 16:24:00 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static	void	fill_between_quo_1(char **ret, char *s, int *i)
{
	while (s[*i])
	{
		*(*ret)++ = s[(*i)++];
		if (s[*i] == 39)
		{
			*(*ret)++ = s[(*i)++];
			*(*ret) = '\0';
			return ;
		}
	}
}

static	void	quo_2_hlp(char **ret, int *i, char *s, t_env *env)
{
	char	*var;

	(*i)++;
	var = expand_var(s, i, env);
	if (!var || !*var)
		return ;
	while (*var)
		*(*ret)++ = *var++;
}

static	void	fill_between_quo_2(char **ret, char *s, int *i, t_env *env)
{
	*(*ret)++ = s[(*i)++];
	while (s[*i])
	{
		if (s[*i] == '$' && is_identifier(s[(*i) + 1]))
			quo_2_hlp(ret, i, s, env);
		else if (s[*i] == 34)
		{
			*(*ret)++ = s[(*i)++];
			*(*ret) = '\0';
			return ;
		}
		else
			*(*ret)++ = s[(*i)++];
		*(*ret) = '\0';
	}
}

static	void	replace_var(char **keep, char *s, int *i, t_env *env)
{
	char	*var;
	char	**ret;
	char	*save;
	bool	flg;

	(*i)++;
	ret = keep;
	flg = false;
	if (s[*i] == '?')
		flg = true;
	var = expand_var(s, i, env);
	save = var;
	if (!var)
		return ;
	while (*var)
		*(*ret)++ = *var++;
	*(*ret) = '\0';
	if (flg)
		free(save);
}

void	modify_cmd(char *ret, char *s, t_env *env)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == 39)
			fill_between_quo_1(&ret, s, &i);
		else if (s[i] == 34)
			fill_between_quo_2(&ret, s, &i, env);
		else if (s[i] == '$' && (is_identifier(s[i + 1]) || s[i + 1] == '?'))
			replace_var(&ret, s, &i, env);
		else if (s[i] == '$' && (s[i + 1] == 34 || s[i + 1] == 39))
			i++;
		else
			*ret++ = s[i++];
	}
	*ret = '\0';
}
