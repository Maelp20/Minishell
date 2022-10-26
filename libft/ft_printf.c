/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:45:36 by yanthoma          #+#    #+#             */
/*   Updated: 2022/07/10 22:35:16 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
//check du caractere dans la premiere chaine
int	ft_check(char c)
{
	size_t	i;
	char	*str;

	i = 0;
	str = "cspiudxX%";
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

//call de la fonction selon e caractere suivant le %
int	ft_call_function(char c, va_list params)
{
	if (c == 'c')
		return (ft_print_c(params));
	else if (c == 's')
		return (ft_print_s(params));
	else if (c == 'i' || c == 'd')
		return (ft_print_id(params));
	else if (c == 'u')
		return (ft_print_u(params));
	else if (c == 'x')
		return (ft_print_x (params));
	else if (c == 'X')
		return (ft_print_xcap(params));
	else if (c == 'p')
		return (ft_print_p(params));
	else if (c == '%')
		return (ft_print_percent());
	return (0);
}

int	ft_printf(const	char *str, ...)
{
	size_t	i;
	size_t	sum;
	va_list	params;

	i = 0;
	sum = 0;
	va_start(params, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] && ft_check(str[i + 1]))
		{
			sum += ft_call_function(str[i + 1], params);
			i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			sum++;
		}
		i++;
	}
	va_end(params);
	return (sum);
}
/*
#include <stdio.h>
int main ()
{
	ft_printf("coucou je mapelle %c gros %d", 'Z', 19);
	printf("%d\n", 19);
}
gcc -Wall -Wextra -Werror main.c src/ft_print_idu.c src/ft_print_s_c_p_per.c 
src/ft_print_xX.c libft/ft_strlen.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c 
libft/ft_putnbr_fd.c
*/