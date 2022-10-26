/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:32:41 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/11 22:32:41 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*dest;

	if (!s)
		return (NULL);
	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
char f_iter(unsigned int i, char c)
{
    i = 1;
	char str;
    str = c + i;
    return (str);
}

#include <stdio.h>

int main()
{
    char str1[] = "abc";
    char* str2;
    str2 = ft_strmapi(str1, *f_iter);
    printf("%s\n", str2);
}*/