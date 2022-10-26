/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 02:00:34 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/03 02:00:34 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

long	ft_atoi(const char *nptr)
{
	int		i;
	long	res;
	long	minus;

	minus = 1;
	res = 0;
	i = -1;
	while ((*nptr >= 9 && *nptr <= 13) || (*nptr == ' '))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minus *= -1;
		nptr++;
	}
	while (*nptr == '0')
		nptr++;
	while (nptr[++i] && nptr[i] >= '0' && nptr[i] <= '9')
		res = (res * 10 + (nptr[i] - 48));
	return (res *= minus);
}
/*
#include <stdio.h>
#include <stdlib.h>
int main (void)
{
    printf("%d\n", ft_atoi("-12"));
    printf("%d\n", ft_atoi("-12"));
}*/
