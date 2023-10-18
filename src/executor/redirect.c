/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:59:55 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/18 17:25:02 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	open_stream(int *fd, t_redir_data *redir_data,
		int *status, char **here_doc)
{
	if (!redir_data->std_fd && redir_data->is_here_doc)
	{
		fd[0] = 0;
		*here_doc = redir_data->text;
		return ;
	}
	if (!redir_data->std_fd)
		fd[0] = open(redir_data->text, F_OK | O_RDONLY);
	else
		fd[1] = open(redir_data->text, redir_data->flags, 0755);
	if (fd[redir_data->std_fd] < 0)
		*status = 1;
	else
		dup2(fd[redir_data->std_fd], redir_data->std_fd);
	close(fd[redir_data->std_fd]);
}

void	make_redirections(t_parser_data *parser_node, int *status)
{
	int				fd[2];
	char			*here_doc;
	t_redir_data	*redir_data;

	fd[0] = 0;
	fd[1] = 1;
	if (!parser_node || !parser_node->redir_data)
		return (0);
	while (redir_data && !*status)
	{
		open_stream(fd, redir_data, status, &here_doc);
		redir_data = redir_data->next;
	}
}

