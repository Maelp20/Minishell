/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:24:36 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/04 00:24:36 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == ((unsigned char)c))
			return ((unsigned char *)s + i);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int main (void)
{  
    char c[50] = "je ne veux pvas";
    char c1[50] = "je ne veux pvas";
    char d = 'v';
    char *a = ft_memchr(c, 'v', 8);
    //memchr(c1, 'v', 4);
    printf("%s\n",a);
    //printf("%s\n", memchr(c1, d, 10));
}*/