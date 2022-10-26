/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_xX.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:45:07 by yanthoma          #+#    #+#             */
/*   Updated: 2022/07/10 22:35:12 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

//print nombre en hexa min et cap
int	ft_print_x(va_list params)
{
	unsigned long long	nb;

	nb = (unsigned long long)va_arg(params, unsigned int);
	ft_basehexa(nb);
	return (ft_strlen_16(nb));
}

int	ft_print_xcap(va_list params)
{
	unsigned long long	nb;

	nb = (unsigned long long)va_arg(params, unsigned int);
	ft_basehexacap(nb);
	return (ft_strlen_16(nb));
}
//longueur des nombre en hexa

int	ft_strlen_16(unsigned long long nb)
{
	size_t	count;

	count = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 16;
		count++;
	}
	return (count);
}
//conversion en hexa minuscule

void	ft_basehexa(unsigned long long nb)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_basehexa(nb / 16);
		write(1, &hex[(unsigned char)nb % 16], 1);
	}
	else
		write(1, &hex[nb], 1);
}

//conversion en hexa maj
void	ft_basehexacap(unsigned long long nb)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (nb >= 16)
	{
		ft_basehexacap(nb / 16);
		write(1, &hex[(unsigned char)nb % 16], 1);
	}
	else
		write(1, &hex[nb], 1);
}
