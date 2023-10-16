/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:45:54 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/16 15:35:33 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

t_parser_data	*init_parser_node(t_lexer_data *lexer_node,
	t_parser_data *parent)
{
	t_parser_data	*parser_node;

	parser_node = NULL;
	if (!lexer_node)
		return (NULL);
	parser_node = malloc(sizeof(t_parser_data));
	if (!parser_node)
		return (NULL);
	parser_node->text = NULL;
	if (lexer_node->lexer_type != redir_notation)
		parser_node->text = ft_strcopy(lexer_node->text);
	parser_node->lexer_type = lexer_node->lexer_type;
	parser_node->left = NULL;
	parser_node->right = NULL;
	parser_node->parent = parent;
	parser_node->cmd_line = NULL;
	parser_node->flags = 0x0;
	parser_node->redir_data = NULL;
	if (parent && !ft_strcmp(parent->text, "|"))
		parser_node->flags |= IS_PIPE;
	return (parser_node);
}

t_lexer_data	*collect_cmd_line(t_lexer_data *lexer_node,
	t_parser_data *parser_node)
{
	t_lexer_data	*curr_lexer_node;
	int				number_cmds;
	int				cmd_i;

	curr_lexer_node = lexer_node;
	number_cmds = 0;
	cmd_i = 0;
	printf("\ncollect_cmd_line ***********\n");
	if (!curr_lexer_node || curr_lexer_node->lexer_type != word)
		return (NULL);
	while (curr_lexer_node && curr_lexer_node->lexer_type == word)
	{
		number_cmds++;
		curr_lexer_node = curr_lexer_node->next;
	}
	curr_lexer_node = lexer_node;
	printf("\n number of cmds:%d\n", number_cmds);
	parser_node->cmd_line = (char **)malloc((number_cmds + 1) * sizeof(char *));
	if (!parser_node->cmd_line)
		return (NULL);
	while (cmd_i < number_cmds)
	{
		parser_node->cmd_line[cmd_i] = ft_strcopy(curr_lexer_node->text);
		curr_lexer_node = curr_lexer_node->next;
		printf("\n cmd line № %d: %s\n", cmd_i, parser_node->cmd_line[cmd_i]);
		cmd_i++;
	}
	parser_node->cmd_line[cmd_i] = NULL;
	if (!curr_lexer_node || ft_strcmp(curr_lexer_node->text, "|"))
	{
		parser_node->flags |= IS_WAIT;
		printf("\n flag is changed: %d\n", parser_node->flags);
	}
	else
		printf("\n Curr lexer node: %s\n", curr_lexer_node->text);
	return (curr_lexer_node);
}

t_parser_data	*create_parser_node(t_lexer_data *lexer_node,
	t_parser_data *parent)
{
	t_parser_data	*parser_node;
	t_lexer_data	*curr_lexer_node;

	curr_lexer_node = lexer_node;
	parser_node = init_parser_node(lexer_node, parent);
	if (parser_node->lexer_type == operator)
		return (parser_node);
	while (curr_lexer_node && curr_lexer_node->lexer_type == redir_notation)
		curr_lexer_node = collect_redir(curr_lexer_node, parser_node);
	if (!parser_node->text && curr_lexer_node
		&& curr_lexer_node->lexer_type == word)
		parser_node->text = ft_strcopy(curr_lexer_node->text);
	while (curr_lexer_node && curr_lexer_node->lexer_type != operator)
	{
		curr_lexer_node = collect_cmd_line(curr_lexer_node, parser_node);
		curr_lexer_node = collect_redir(curr_lexer_node, parser_node);
	}
	return (parser_node);
}
