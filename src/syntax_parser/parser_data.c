/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:45:54 by tklimova          #+#    #+#             */
/*   Updated: 2023/11/28 15:22:33 by tklimova         ###   ########.fr       */
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

t_lexer_data	*fill_cmd_line(int *cmd_i, int number_cmds,
			t_parser_data *parser_node, t_lexer_data *curr_lexer_node)
{
	while (*cmd_i < number_cmds)
	{
		parser_node->cmd_line[*cmd_i] = ft_strcopy(curr_lexer_node->text);
		curr_lexer_node = curr_lexer_node->next;
		(*cmd_i)++;
	}
	parser_node->cmd_line[*cmd_i] = NULL;
	return (curr_lexer_node);
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
	if (!curr_lexer_node || curr_lexer_node->lexer_type != word)
		return (curr_lexer_node);
	while (curr_lexer_node && curr_lexer_node->lexer_type == word)
	{
		number_cmds++;
		curr_lexer_node = curr_lexer_node->next;
	}
	curr_lexer_node = lexer_node;
	parser_node->cmd_line = (char **)malloc((number_cmds + 1) * sizeof(char *));
	if (!parser_node->cmd_line)
		return (NULL);
	curr_lexer_node = fill_cmd_line(&cmd_i, number_cmds,
			parser_node, curr_lexer_node);
	return (curr_lexer_node);
}

void	print_parser_node(t_parser_data *pars_node)
{
	t_redir_data	*redirs;
	int				i;

	redirs = NULL;
	i = 0;
	if (!pars_node)
		return ;
	printf("[LOG] AST NODE: text: %s, type: %d\n", pars_node->text,
		pars_node->lexer_type);
	printf("[LOG] flags: %d\n", pars_node->flags);
	redirs = pars_node->redir_data;
	while (redirs)
	{
		printf("[LOG] Redir № %d, direction: %d, flags: %d, file name: %s \n",
			i, redirs->std_fd, redirs->flags, redirs->text);
		redirs = redirs->next;
		i++;
	}
	i = 0;
	while (pars_node->cmd_line && pars_node->cmd_line[i])
	{
		printf("[LOG] [%s] ", pars_node->cmd_line[i]);
		i++;
	}
	printf("\n");
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
	{
		parser_node->text = ft_strcopy(curr_lexer_node->text);
		parser_node->lexer_type = curr_lexer_node->lexer_type;
	}
	while (curr_lexer_node && curr_lexer_node->lexer_type != operator)
	{
		curr_lexer_node = collect_cmd_line(curr_lexer_node, parser_node);
		curr_lexer_node = collect_redir(curr_lexer_node, parser_node);
	}
	if (!curr_lexer_node || ft_strcmp(curr_lexer_node->text, "|"))
		parser_node->flags |= IS_WAIT;
	print_parser_node(parser_node);
	return (parser_node);
}
