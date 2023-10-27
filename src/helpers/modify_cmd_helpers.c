/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_cmd_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:18:41 by plandolf          #+#    #+#             */
/*   Updated: 2023/10/27 17:01:14 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*copy_variable_name(char **r_ptr, char *variable_name)
{
	int	var_index;

	var_index = 0;
	(*r_ptr)++;
	while (**r_ptr && ((**r_ptr >= 'A' && **r_ptr <= 'Z') || **r_ptr == '_'
			|| (var_index > 0 && **r_ptr >= '0' && **r_ptr <= '9')))
	{
		variable_name[var_index++] = **r_ptr;
		(*r_ptr)++;
	}
	variable_name[var_index] = '\0';
	return (variable_name);
}

void	write_replacement_or_variable(char **w_ptr, char *variable_name,
	t_data *data)
{
	char	*replacement;
	int		i;
	int		var_index;

	var_index = ft_strlen(variable_name);
	i = var_index;
	while (i >= 0)
	{
		variable_name[i] = '\0';
		replacement = get_env(variable_name, data->env_vars);
		if (replacement && *replacement)
		{
			while (*replacement)
				*(*w_ptr)++ = *replacement++;
			return ;
		}
		i--;
	}
	*(*w_ptr)++ = '$';
	while (*variable_name)
		*(*w_ptr)++ = *variable_name++;
}

char	*copy_var_and_get_next(char *r_ptr, char **w_ptr, t_data *data)
{
	char	variable_name[100];

	copy_variable_name(&r_ptr, variable_name);
	write_replacement_or_variable(w_ptr, variable_name, data);
	return (r_ptr);
}

void	handle_quotes(char **r_ptr, char **w_ptr, bool *in_single_quotes)
{
	*(*w_ptr)++ = **r_ptr;
	(*r_ptr)++; 
	while (**r_ptr != '\'' && **r_ptr != '\0')
	{
		*(*w_ptr)++ = **r_ptr;
		(*r_ptr)++;
	}
	if (**r_ptr == '\'')
	{
		*(*w_ptr)++ = **r_ptr;
		(*r_ptr)++;
	}
	*in_single_quotes = !(*in_single_quotes);
}

void	init_pointers(t_ptrs *ptrs, char *str, bool *in_single_quotes)
{
	ptrs->temp = (char *)malloc(ft_strlen(str) + 1);
	ptrs->r_ptr = str;
	ptrs->w_ptr = ptrs->temp;
	*in_single_quotes = false;
}
