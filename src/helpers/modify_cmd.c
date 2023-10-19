/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:42:42 by plandolf          #+#    #+#             */
/*   Updated: 2023/10/19 11:45:27 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static char	*copy_var_and_get_next(char *r_ptr, char **w_ptr, t_data *data)
{
	char	variable_name[100];
	int		var_index;
	char	*replacement;
	char	*var_ptr;

	r_ptr++;
	var_index = 0;
	while (*r_ptr && (ft_isalpha(*r_ptr) || *r_ptr == '_'))
		variable_name[var_index++] = *r_ptr++;
	variable_name[var_index] = '\0';
	replacement = get_env(variable_name, data);
	if (replacement)
		while (*replacement)
			*(*w_ptr)++ = *replacement++;
	else
	{
		*(*w_ptr)++ = '$';
		var_ptr = variable_name;
		while (*var_ptr)
			*(*w_ptr)++ = *var_ptr++;
	}
	return (r_ptr);
}

static void	handle_quotes(char **r_ptr, char **w_ptr, char quote_type)
{
	(*r_ptr)++; 
	while (**r_ptr != quote_type && **r_ptr != '\0')
		*(*w_ptr)++ = *(*r_ptr)++;
	if (**r_ptr == quote_type)
		(*r_ptr)++;
}

static void	init_pointers(t_ptrs *ptrs, char *str, bool *in_single_quotes)
{
	ptrs->temp = (char *)malloc(ft_strlen(str) + 1);
	ptrs->r_ptr = str;
	ptrs->w_ptr = ptrs->temp;
	*in_single_quotes = false;
}

static void	process_char(t_ptrs *ptrs, bool *in_single_quotes, t_data *data)
{
	if (*ptrs->r_ptr == '\'' && !(*in_single_quotes))
	{
		handle_quotes(&ptrs->r_ptr, &ptrs->w_ptr, '\'');
		*in_single_quotes = !(*in_single_quotes);
	}
	else if (*ptrs->r_ptr == '"' && !(*in_single_quotes))
		*ptrs->w_ptr++ = *ptrs->r_ptr++;
	else if (*ptrs->r_ptr == '$' && !(*in_single_quotes))
		ptrs->r_ptr = copy_var_and_get_next(ptrs->r_ptr,
				&ptrs->w_ptr, data);
	else
		*ptrs->w_ptr++ = *ptrs->r_ptr++;
}

void	modify_cmd(char *str, t_data *data)
{
	t_ptrs	ptrs;
	bool	in_single_quotes;

	init_pointers(&ptrs, str, &in_single_quotes);
	if (!ptrs.temp)
		return ;
	while (*ptrs.r_ptr)
		process_char(&ptrs, &in_single_quotes, data);
	*ptrs.w_ptr = '\0';
	ft_strlcpy(str, ptrs.temp, ft_strlen(ptrs.temp) + 1);
	free(ptrs.temp);
}
