/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:47:25 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/04 00:47:25 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
    char str[50] = "je ne veux pas travailler c'est chiant";
    char strb[50] = "je ne veux pas traivailler c'est chiant";
    
    memset(str + 13, '.', 8);
    ft_memset(strb + 13, '.', 8);
    //int i = 0;

    printf("After memset():  %s\n", str);
    printf("truc\n");
    printf("After memset():  %s\n", strb);
    return 0;
}*/