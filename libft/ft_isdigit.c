/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:19:35 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/04 00:19:35 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (2048);
	else
		return (0);
}
/*#include <ctype.h>
#include <stdio.h>
int main (void)
{
    printf("%d\n", isdigit('8'));
    printf("%d\n", ft_isdigit('8'));
}*/