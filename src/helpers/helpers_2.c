/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:36:46 by pascal            #+#    #+#             */
/*   Updated: 2023/12/19 15:20:29 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

ssize_t	find_c(char *s, char c)
{
	ssize_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (i);
		s++;
		i++;
	}
	return (-1);
}

static char	**allocate_env_array(int count)
{
	char	**envp_array;

	envp_array = (char **)malloc((count + 1) * sizeof(char *));
	return (envp_array);
}

static void	free_env_array(char **envp_array, int count)
{
	while (count--)
		free(envp_array[count]);
	free(envp_array);
}

static int	populate_env_array(t_env *temp, char **envp_array)
{
	int		i;
	char	*temp_str;

	i = 0;
	while (temp)
	{
		temp_str = ft_strjoin(temp->var, "=");
		envp_array[i] = ft_strjoin(temp_str, temp->value);
		free(temp_str);
		if (!envp_array[i])
			return (i);
		i++;
		temp = temp->next;
	}
	return (i);
}

char	**env_list_to_array(t_env *env_list)
{
	int		count;
	t_env	*temp;
	char	**envp_array;
	int		last_index;

	count = 0;
	temp = env_list;
	while (temp) 
	{
		count++;
		temp = temp->next;
	}
	temp = env_list;
	envp_array = allocate_env_array(count);
	if (!envp_array)
		return (NULL);
	last_index = populate_env_array(temp, envp_array);
	if (last_index < count)
	{
		free_env_array(envp_array, last_index);
		return (NULL);
	}
	envp_array[last_index] = (NULL);
	return (envp_array);
}
