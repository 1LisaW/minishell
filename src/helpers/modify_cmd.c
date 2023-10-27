/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:42:42 by plandolf          #+#    #+#             */
/*   Updated: 2023/10/27 17:03:36 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	process_char(t_ptrs *ptrs, bool *in_single_quotes, t_data *data)
{
	if (*ptrs->r_ptr == '\'' && !(*in_single_quotes))
		handle_quotes(&ptrs->r_ptr, &ptrs->w_ptr, in_single_quotes);
	else if (*ptrs->r_ptr == '$' && !(*in_single_quotes))
		ptrs->r_ptr = copy_var_and_get_next(ptrs->r_ptr, &ptrs->w_ptr, data);
	else
		*ptrs->w_ptr++ = *ptrs->r_ptr++;
}

void	modify_cmd(char *str, t_env *data)
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
