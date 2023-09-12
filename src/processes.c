/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:11:45 by root              #+#    #+#             */
/*   Updated: 2023/09/12 13:37:41 by tklimova         ###   ########.fr       */
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
	close(fd1[0]);
	p = fork();
	if (p < 0)
	{
		perror("Fork failed");
		return (-2);
	}
	return (p);
}
