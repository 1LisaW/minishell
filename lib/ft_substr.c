/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:22:31 by plandolf          #+#    #+#             */
/*   Updated: 2023/09/27 16:03:10 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lib.h"

char	*ft_substr(char *s, unsigned int start, int len)
{
	char	*sub;
	int		i;

	i = 0;
	if (start >= (unsigned int)ft_strlen(s))
	{
		sub = malloc(sizeof(char));
		if (sub == NULL)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = malloc((len * sizeof(char)) + 1);
	if (sub == NULL)
		return (NULL);
	while (i < len && s[start] != '\0')
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
