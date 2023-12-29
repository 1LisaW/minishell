/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:23:52 by root              #+#    #+#             */
/*   Updated: 2023/12/29 18:34:12 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	init_data(t_data *data)
{
	data->lexer_data = NULL;
	data->parser_data = NULL;
	data->env_vars = NULL;
	data->env_del = NULL;
	data->exec_data = NULL;
}

void	destroy_parser_data(t_parser_data *parser_data)
{
	char	**tmp_cmd_line;

	if (!parser_data)
		return ;
	if (parser_data->left)
		destroy_parser_data(parser_data->left);
	if (parser_data->right)
		destroy_parser_data(parser_data->right);
	if (parser_data->text)
		free(parser_data->text);
	parser_data->text = NULL;
	tmp_cmd_line = parser_data->cmd_line;
	while (tmp_cmd_line && *tmp_cmd_line)
	{
		free(*tmp_cmd_line);
		tmp_cmd_line++;
	}
	if (parser_data->cmd_line)
		free(parser_data->cmd_line);
	destroy_redir_lst(parser_data);
	parser_data->cmd_line = NULL;
	parser_data->parent = NULL;
	if (parser_data)
		free(parser_data);
	parser_data = NULL;
}

void	destroy_data(t_data *data)
{
	if (data && data->lexer_data)
	{
		delete_lexer_data(data);
		destroy_parser_data(data->parser_data);
		data->parser_data = NULL;
	}
}
