/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:31:20 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/27 18:29:31 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_valid_flag(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
	{
		while (str[++i])
			if (str[i] != 'n')
				return (0);
		return (1);
	}
	return (0);
}

int	ft_echo(t_data *data)
{
	int	i;
	int	flag;

	g_var.g_status = 0;
	if (!data->args[1])
		return (printf("\n"), 0);
	i = 1;
	flag = 0;
	while (data->args[i] && is_valid_flag(data->args[i]))
	{
		flag = 1;
		i++;
	}
	while (data->args[i] && data->args[i + 1])
		printf("%s ", data->args[i++]);
	if (data->args[i])
		printf("%s", data->args[i]);
	if (flag == 0)
		printf("\n");
	return (0);
}
