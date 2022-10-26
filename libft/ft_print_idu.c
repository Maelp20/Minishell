/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_idu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:43:15 by yanthoma          #+#    #+#             */
/*   Updated: 2022/07/10 22:34:04 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_strlen_nb(int nb)
{
	size_t			count;
	long long int	nb1;

	count = 0;
	nb1 = nb;
	if (nb1 == 0)
		count++;
	if (nb1 < 0)
	{
		nb1 *= -1;
		count++;
	}
	while (nb1 > 0)
	{
		nb1 /= 10;
		count++;
	}
	return (count);
}

int	ft_strlen_nbu(unsigned int nb)
{
	size_t					count;
	unsigned long long int	nb1;

	count = 0;
	nb1 = nb;
	if (nb1 == 0)
		count++;
	while (nb1 > 0)
	{
		nb1 /= 10;
		count++;
	}
	return (count);
}

void	ft_putnbr_u(unsigned int n)
{
	char	c;
	long	a;

	a = n;
	if (a >= 0 && a <= 9)
	{
		c = a + '0';
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr_u(a / 10);
		ft_putnbr_u(a % 10);
	}
}

int	ft_print_id(va_list args)
{
	int	nb;

	nb = (int)va_arg(args, int);
	ft_putnbr_fd(nb, 1);
	return (ft_strlen_nb(nb));
}

int	ft_print_u(va_list args)
{
	unsigned long long int	nb;

	nb = (unsigned long long int)va_arg(args, unsigned int);
	ft_putnbr_u(nb);
	return (ft_strlen_nbu(nb));
}
