/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:11:45 by root              #+#    #+#             */
/*   Updated: 2023/09/11 15:54:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int	create_pipe(int *pipefd)
{
	if (pipe(pipefd) < 0)
	{
		perror("Pipe failed");
		return (-1);
	}
	return (0);
}

int	create_process(int *fd1, int *fd2)
{
	pid_t	p;

	if (create_pipe(fd1) || create_pipe(fd2))
		return (-1);
	//dup2(fd1[0], stdin);
	close(fd1[0]);
	p = fork();
	if (p < 0)
	{
		perror("Fork failed");
		return (-2);
	}
	// if (!p)
	// {
	// 	readline(NULL);
	// }
	return (p);
}
