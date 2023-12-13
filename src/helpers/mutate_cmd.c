/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutate_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:12:13 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/13 13:34:44 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	count_expand_var_len(char **str, t_env *env, int idx)
{
	int		keep;
	char	*var;
	char	*n_str;

	keep = 0;
	n_str = NULL;
	if ((*str)[keep + idx] == '?')
	{
		n_str = ft_itoa(g_gb.exit_st);
		return (keep += ft_strlen(n_str), free(n_str), (*str)++, keep);
	}
	while (is_identifier(*((*str) + keep + idx)))
		keep++;
	n_str = ft_substr(*str + idx, 0, keep);
	var = get_env(n_str, env);
	(*str) += keep;
	if (!var || !*var)
		return (free(n_str), n_str = NULL, 0);
	keep = ft_strlen(var);
	return (free(n_str), n_str = NULL, keep);
}

int	ft_substr_len_till_char(char **str, int ch, t_env *env)
{
	int	len;
	int	env_len;

	len = 1;
	env_len = 0;
	while (ch && (*str)[len] && (*str)[len] != ch)
	{
		if (ch == 34 && (*str)[len] == '$' && (*str)[len + 1]
			&& is_identifier((*str)[len + 1]))
		{
			*str += 1;
			env_len += count_expand_var_len(str, env, len);
		}
		else
			len++;
	}
	if (ch && (*str)[len] == ch)
		len++;
	while (!ch && (*str)[len] && (*str)[len] != 39
			&& (*str)[len] != 34 && (*str)[len] != '$')
		len++;
	*str += len;
	return (len + env_len);
}

void	calc_len_after_env_replacement(int *len, char *str, t_env *env)
{
	while (str && *str)
	{
		if (*str == 39)
			*len += ft_substr_len_till_char(&str, 39, env);
		else if (*str == 34)
			*len += ft_substr_len_till_char(&str, 34, env);
		else if (*str == '$' && (*str) + 1 && is_identifier(*(str + 1)))
		{
			str++;
			*len += count_expand_var_len(&str, env, 0);
		}
		else
		{
			*len += ft_substr_len_till_char(&str, 0, env);
		}
	}
}

void	mutate_cmd(char **str, t_env *env)
{
	int		len_with_env;
	char	*res;

	len_with_env = 0;
	calc_len_after_env_replacement(&len_with_env, *str, env);
	res = malloc(sizeof(char) * (len_with_env + 1));
	modify_cmd(res, *str, env);
	free(*str);
	*str = new_cmd(res, NULL);
}

void	mutate_parser_node(t_parser_data *parser_node, t_data *data)
{
	t_redir_data	*redir_node;
	char			**cmd;

	redir_node = parser_node->redir_data;
	cmd = parser_node->cmd_line;
	while (redir_node)
	{
		mutate_cmd(&redir_node->text, data->env_vars);
		redir_node = redir_node->next;
	}
	if (parser_node->lexer_type == word)
	{
		mutate_cmd(&parser_node->text, data->env_vars);
		while (*cmd)
		{
			mutate_cmd(&(*cmd), data->env_vars);
			cmd += 1;
		}
	}
}
