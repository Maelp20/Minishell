/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:41:23 by yanthoma          #+#    #+#             */
/*   Updated: 2022/05/06 13:17:25 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_len(int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len = 1;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*dest;
	long long	i;
	long long	x;

	x = n;
	i = ft_len(x);
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	dest[i] = '\0';
	if (x < 0)
	{	
		x *= -1;
		dest[0] = '-';
	}
	else if (x == 0)
		dest[0] = '0';
	i--;
	while (x > 0)
	{
		dest[i--] = (x % 10) + 48;
		x /= 10;
	}
	return (dest);
}
/*
int main (void)
{
	printf("%s\n", ft_itoa(INT_MIN));
}*/
