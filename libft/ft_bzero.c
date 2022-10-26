/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:31:25 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/03 16:31:25 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = '\0';
		i++;
	}
}
/*
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main (void)
{
    char c[50] = "abcdef";
    char c1[50] = "abcdef";
	int i = 0;
    bzero(c + 2, 3);
    ft_bzero(c1 + 2, 1);
	while(i < 14)
	{
		write(1, &c1[i], 1);
		i++;
	}
    printf("\n%s\n", c1);
    printf("%s\n", c1);
}*/