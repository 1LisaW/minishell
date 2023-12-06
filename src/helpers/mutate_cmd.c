/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutate_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:12:13 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/06 16:38:20 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static	void	get_substr_single_q(char **res, char *str, int *i)
{
	char	*tmp;
	char	*substr;
	int		idx;

	idx = *i;
	tmp = NULL;

	while (str[idx])
	{
		idx++;
		if (!str[idx] || str[idx] == 39)
			break ;
	}
	idx++;
	substr = ft_substr(str, *i, idx - *i + 1);
	*i = idx;
	tmp = ft_strjoin(*res, substr);
	free(*res);
	free(substr);
	*res = tmp;
}

static	void	quo_2_hlp(char **res, int *i, char *s, t_env *env)
{
	char	*var;
	char	*tmp;

	(*i)++;
	var = expand_var(s, i, env);
	if (!var || !*var)
		return ;
	tmp = ft_strjoin(*res, var);
	free(*res);
	free(var);
	*res = tmp;

}

static	void	get_substr_dowble_q(char **ret, char *str, int *i, t_env *env)
{
	char	*tmp;
	// char	*substr;
	int		idx;

	idx = *i;
	tmp = NULL;

	while (str[idx])
	{
		idx++;
		if (str[idx] == '$' && is_identifier(str[idx + 1]))
		{
			quo_2_hlp(ret, &idx, str, env);
			*i =idx;
		}
		if (!str[idx] || str[idx] == 39)
			break ;
	}
}

void	mutate_cmd(char *str, t_env *env)
{
	int		i;
	char	*res;
	// char	*tmp;

	i = 0;
	res = malloc(sizeof(str));
	while (str && str[i])
	{
		if (str[i] == 39)
			get_substr_single_q(&res, str, &i);
		else if (str[i] == 34)
			get_substr_dowble_q(&res, str, &i, env);
		// else if (str[i] == '$' && (is_identifier(str[i + 1])
		// 		|| str[i + 1] == '?'))
		// 	replace_var(&tmp, str, &i, env);
		// else if (str[i] == '$' && (str[i + 1] == 34 || str[i + 1] == 39))
		// 	i++;
		// else
			// *tmp++ = str[i++];
	}
	// *tmp = '\0';
	printf("\nmodified to: %s, %s\n", res, str);
}