/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutate_cmd_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 00:09:51 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/29 00:15:14 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	ft_update_for_empty_cmd(t_parser_data *parser_node)
{
	if (!*parser_node->text)
	{
		free(parser_node->text);
		parser_node->text = ft_strcopy("\'\'");
		free(parser_node->cmd_line[0]);
		parser_node->cmd_line[0] = ft_strcopy("\'\'");
	}
}
