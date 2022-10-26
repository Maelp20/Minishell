/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s_c_p_per.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:44:49 by yanthoma          #+#    #+#             */
/*   Updated: 2022/07/10 22:34:15 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

//print un caractere et renvoie longueur a 1
int	ft_print_c(va_list params)
{
	char	c;

	c = (char)va_arg(params, int);
	ft_putchar_fd(c, 1);
	return (1);
}

//print une chaine
int	ft_print_s(va_list params)
{
	char	*s;

	s = (char *)va_arg(params, char *);
	if (s)
	{
		ft_putstr_fd(s, 1);
		return (ft_strlen(s));
	}
	else
	{
		ft_putstr_fd("(null)", 1);
		return (ft_strlen("(null)"));
	}
}

//print un %
int	ft_print_percent(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}

//print une adresse en hexa
int	ft_print_p(va_list args)
{
	unsigned long long int	addr;

	addr = (unsigned long long int)va_arg(args, void *);
	if (addr)
	{
		ft_putstr_fd("0x", 1);
		ft_basehexa(addr);
		return (ft_strlen_16(addr) + 2);
	}
	ft_putstr_fd("(nil)", 1);
	return (ft_strlen("(nil)"));
}
