/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parser_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:26:17 by tklimova          #+#    #+#             */
/*   Updated: 2023/11/01 12:37:07 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

t_lexer_data	*get_operator(t_lexer_data **head_node,
	t_lexer_data **tail_node, char **oper)
{
	t_lexer_data	**lexer_node;

	lexer_node = NULL;
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
	}
	else
	{
		subtree_root = create_parser_node(*lexer_head, parent);
		return (subtree_root);
	}
	while ((*left_tail) && (*left_tail)->next
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

	tail_lexer_node = &data->lexer_data;
	while ((*tail_lexer_node)->next)
		tail_lexer_node = &(*tail_lexer_node)->next;
	data->parser_data = build_subtree(&data->lexer_data,
			tail_lexer_node,
			NULL, oper_arr);
	free(oper_arr);
}
