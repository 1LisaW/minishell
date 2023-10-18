/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:11:22 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/18 15:16:27 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	get_next_node(t_parser_data **curr_node, t_parser_data **prev_node)
{
	*prev_node = (*curr_node)->left;
	while ((*prev_node)->right && (*prev_node)->right != *curr_node)
		*prev_node = (*prev_node)->right;
	if (!(*prev_node)->right)
	{
		(*prev_node)->right = *curr_node;
		*curr_node = (*curr_node)->left;
		return (0);
	}
	return (1);
}

void	morris_traversal(t_parser_data *parser_data, int *prev_fd, int *status)
{
	t_parser_data	*curr_node;
	t_parser_data	*prev_node;

	curr_node = parser_data;
	while (curr_node)
	{
		if (!curr_node->left)
		{
			printf("%s   ", curr_node->text);
			execute_process(prev_fd, curr_node, status);
			curr_node = curr_node->right;
		}
		else if (get_next_node(&curr_node, &prev_node))
		{
			prev_node->right = NULL;
			printf("%s   ", curr_node->text);
			execute_process(prev_fd, curr_node, status);
			curr_node = curr_node->right;
		}
	}
}

void	executor(t_data *data)
{
	int	prev_fd;

	prev_fd = dup(STDIN_FILENO);
	morris_traversal(data->parser_data, &prev_fd, &data->status_code);
}
