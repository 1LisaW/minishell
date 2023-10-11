/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:45:54 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/05 13:23:01 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

t_parser_data	*create_parser_node(t_lexer_data *lexer_node,
	t_parser_data *parent)
{
	t_parser_data	*parser_node;

	parser_node = NULL;
	if (!lexer_node)
		return (NULL);
	parser_node = malloc(sizeof(t_parser_data));
	if (!parser_node)
		return (NULL);
	parser_node->text = ft_strcopy(lexer_node->text);
	parser_node->lexer_type = lexer_node->lexer_type;
	parser_node->left = NULL;
	parser_node->right = NULL;
	parser_node->parent = parent;
	parser_node->cmd_line = NULL;
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
	if (!curr_lexer_node || curr_lexer_node != word)
		return (NULL);
	while (curr_lexer_node && curr_lexer_node->lexer_type == word)
	{
		number_cmds++;
		curr_lexer_node = curr_lexer_node->next;
	}
	parser_node->cmd_line = (char **)malloc((number_cmds + 1) * sizeof(char *));
	if (!parser_node->cmd_line)
		return (NULL);
	while (cmd_i < number_cmds)
	{
		parser_node->cmd_line[cmd_i] = ft_strcopy(curr_lexer_node->text);
		curr_lexer_node = curr_lexer_node->next;
		cmd_i++;
	}
	parser_node->cmd_line[cmd_i] = NULL;
	return (curr_lexer_node);
}

t_lexer_data	*get_operator(t_lexer_data **head_node,
	t_lexer_data **tail_node, char **oper)
{
	t_lexer_data	**lexer_node;

	lexer_node = NULL;
	printf("head_node: %s, tailnode:%s\n",
		(*head_node)->text, (*tail_node)->text);
	while (*oper)
	{
		lexer_node = head_node;
		while (*lexer_node && lexer_node != tail_node)
		{
			if (!ft_strcmp((*lexer_node)->text, *oper))
				return (*lexer_node);
			lexer_node = &(*lexer_node)->next;
		}
		oper++;
	}
	if (lexer_node == tail_node)
		return (NULL);
	return (*lexer_node);
}

t_parser_data	*build_subtree(t_lexer_data **lexer_head,
	t_lexer_data **lexer_tail, t_parser_data *parent, char **oper)
{
	t_parser_data	*subtree_root;
	t_lexer_data	*oper_node;
	t_lexer_data	**left_tail;

	subtree_root = NULL;
	left_tail = lexer_head;
	oper_node = get_operator(lexer_head, lexer_tail, oper);
	if (oper_node)
	{
		subtree_root = create_parser_node(oper_node, parent);
		printf("node (if oper_node): %s\n", subtree_root->text);
		if (parent)
			printf("parent: %s\n", parent->text);
	}
	else
	{
		subtree_root = create_parser_node(*lexer_head, parent);
		printf("node: %s \n", subtree_root->text);
		if (parent)
			printf("parent: %s\n", parent->text);
		collect_cmd_line(*lexer_head, subtree_root);
		return (subtree_root);
	}
	while ((*left_tail)->next
		&& ft_strcmp((*left_tail)->next->text, oper_node->text))
		left_tail = &(*left_tail)->next;
	subtree_root->left = build_subtree(lexer_head, left_tail,
			subtree_root, oper);
	subtree_root->right = build_subtree(&(*left_tail)->next->next, lexer_tail,
			subtree_root, oper);
	return (subtree_root);
}

void	build_tree(t_data *data, char **oper_arr)
{
	t_lexer_data	**tail_lexer_node;
	int				max_pipes;

	data->pipes_amount = 0;
	max_pipes = 0;
	tail_lexer_node = &data->lexer_data;
	while ((*tail_lexer_node)->next)
	{
		if ((*tail_lexer_node)->lexer_type == operator)
		{
			if (ft_strcmp((*tail_lexer_node)->text, "|"))
				max_pipes = 0;
			else
				max_pipes++;
			if (data->pipes_amount < max_pipes)
				data->pipes_amount = max_pipes;
		}
		tail_lexer_node = &(*tail_lexer_node)->next;
	}
	data->parser_data = build_subtree(&data->lexer_data,
			tail_lexer_node,
			NULL, oper_arr);
	free(oper_arr);
}
