/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:12:18 by plandolf          #+#    #+#             */
/*   Updated: 2023/12/04 11:59:55 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static int	get_error_code(int err_code, bool set_err_code)
{
	static int	error_code = 0;

	if (set_err_code)
		error_code = err_code;
	return (error_code);
}

void	set_error_code(int err_code)
{
	static bool	ctrlc = false;

	if (ctrlc)
	{
		ctrlc = false;
		return ;
	}
	if (err_code == 130)
		ctrlc = true;
	get_error_code(err_code, true);
}

int	get_error(void)
{
	return (get_error_code(0, false));
}
