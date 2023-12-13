/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:17:36 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/13 13:28:03 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/mini_shell.h"

// void	print_error(char *text, char *errmsg, t_exec_data *exec_data)
// {
// 	int	fd[2];

// 	fd[0] = dup(STDOUT_FILENO);
// 	fd[1] = dup(STDERR_FILENO);
// 	dup2(STDERR_FILENO, STDOUT_FILENO);
// 	close(STDERR_FILENO);
// 	printf("%s:%s\n", text, errmsg);
// 	dup2(fd[0], STDOUT_FILENO);
// 	dup2(fd[1], STDERR_FILENO);
// 	close(fd[0]);
// 	close(fd[1]);
// }