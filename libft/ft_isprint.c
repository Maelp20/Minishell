/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:19:47 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/04 00:19:47 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	else
		return (0);
}
/*#include <ctype.h>
#include <stdio.h>
int main (void)
{
    printf("%d\n", isprint('A'));
    printf("%d\n", ft_isprint('A'));
}*/