/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 23:46:03 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/04 23:46:03 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checkchar(char const *set, char c)
{
	size_t	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*dest;
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_checkchar(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	while (j > i && ft_checkchar(set, s1[j - 1]))
		j--;
	dest = malloc(sizeof(char) * (j - i + 1));
	if (!dest)
		return (NULL);
	k = 0;
	while (i < j)
	{
		dest[k++] = s1[i++];
	}
	dest[k] = '\0';
	return (dest);
}
/*
#include <stdio.h>
int main (void)
{
	char *a = "hjk je be veux pas travailler hjp";
	char *b = "khp";
	printf("%s\n",ft_strtrim(a,b));
}*/