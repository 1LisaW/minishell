/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:11:22 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/03 16:12:50 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

t_parser_data	*get_lexer_node(t_parser_data *parser_data)
{
	if (parser_data == NULL)
		return (NULL);
	get_lexer_node(parser_data->left);
	get_lexer_node(parser_data->right);
	printf("Node: %s\n", parser_data->text);
	return (parser_data);
}

void	executer(t_data *data)
{
	get_lexer_node(data->parser_data);
}
