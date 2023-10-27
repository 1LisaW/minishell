/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:06:53 by plandolf          #+#    #+#             */
/*   Updated: 2023/10/17 14:37:01 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strchr(char *str, int c)
{
	unsigned int	i;
	char			*first;

	first = NULL;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == (char)c)
		{
			first = (char *)&str[i];
			break ;
		}
		i++;
	}
	if ((char)c == str[i])
		return ((char *)&str[i]);
	return (first);
}
