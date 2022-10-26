/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:55:24 by yanthoma          #+#    #+#             */
/*   Updated: 2022/05/06 13:06:29 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ls;
	size_t	ld;
	size_t	i;

	ls = ft_strlen(src);
	ld = ft_strlen(dst);
	if (size == 0 || ld >= size)
		return (ls + size);
	i = 0;
	while (src[i] && (i + ld + 1 < size))
	{
		dst[ld + i] = src[i];
		i++;
	}
	dst[i + ld] = '\0';
	return (ld + ls);
}
/*
#include <stdio.h>
int main (void)
{
    char c[17] = "je n'ai pas envi";
    char c1[4] = "peux";
    int n = 0;

    n = ft_strlcat(c, c1, 25);
    printf ("%s\n", c);
    printf ("%d\n", n);
}*/
