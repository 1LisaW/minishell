/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:06:53 by plandolf          #+#    #+#             */
/*   Updated: 2023/05/06 16:45:17 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strchr(const char *str, int c)
{
	unsigned int	i;
	char			*first;

	first = NULL;
	i = 0;
	while (str[i])
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
