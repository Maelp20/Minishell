/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:45:22 by yanthoma          #+#    #+#             */
/*   Updated: 2022/07/10 22:24:25 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"

int		ft_strlen_nb(int nb);
int		ft_strlen_nbu(unsigned int nb);
void	ft_putnbr_u(unsigned int n);
int		ft_print_id(va_list args);
int		ft_print_u(va_list args);

int		ft_print_x(va_list params);
int		ft_print_xcap(va_list params);
int		ft_strlen_16(unsigned long long nb);
void	ft_basehexa(unsigned long long nb);
void	ft_basehexacap(unsigned long long nb);

int		ft_print_c(va_list params);
int		ft_print_s(va_list params);
int		ft_print_percent(void);
int		ft_print_p(va_list args);

int		ft_printf(const char *str, ...);
int		ft_call_function(char c, va_list params);
int		ft_check(char c);

#endif
