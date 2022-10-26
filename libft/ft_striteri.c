/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:48:07 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/11 22:48:07 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
/*
void f_iter(unsigned int i, char *str)
{
    int i;
	while (str[i])
	{
		str[i] += 1;
		i++;
	}
}

#include <stdio.h>

int main()
{
    char str1[] = "abc";
    ft_striteri(str1, *f_iter);
    printf("%s\n", str1);
}
*/