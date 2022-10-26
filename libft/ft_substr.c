/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 01:25:33 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/04 01:25:33 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	if (start > i)
		return (ft_calloc(1, sizeof(char)));
	if (start < i)
		j = i - start;
	if (j > len)
		j = len;
	dest = malloc(sizeof(char) * (j + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s + start, j + 1);
	return (dest);
}

/*
#include <stdio.h>
int main()
{
    char *src = "flemme de tester tout ca";
    int m = 3;
    int n = 6;
    char *a = ft_substr(src, m, n);
    printf("%s\n", a);
}*/