/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:42:59 by plandolf          #+#    #+#             */
/*   Updated: 2023/10/19 11:48:49 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <bsd/string.h>
#include <unistd.h>
#include "lib.h"

int	ft_strlcpy(char *dst, char *src, int size)
{
	char		*d;
	const char	*s;
	int			n;
	int			r;

	d = dst;
	s = src;
	n = size;
	r = 0;
	if (n != 0)
	{
		while (--n != 0)
		{
			if (*s == '\0')
				break ;
			*d++ = *s++;
		}
		*d = '\0';
	}
	while (src[r] != '\0')
		r++;
	return (r);
}
