/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:23:52 by root              #+#    #+#             */
/*   Updated: 2023/09/18 12:59:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	init_data(t_data *data)
{
	data->lexer_data = NULL;
	data->parser_data = NULL;
	data->env_vars = NULL;
	data->env_del = NULL;
}

void	destroy_data(t_data *data)
{
	if (data && data->lexer_data)
	{
		delete_lexer_data(data->lexer_data);
	}
}
