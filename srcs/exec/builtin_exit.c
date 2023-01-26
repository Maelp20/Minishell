/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:32:55 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/26 17:39:29 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* pour EXIT builtin :
	ATTENTION : la valeur de retour sera entre 0 et 255. exit doit tout 
	nettoyer (free et close).
 */

int	check_long_neg(char *str)
{
	int		i;
	char	*reference;

	i = -1;
	reference = "-9223372036854775808";
	while (str[++i] && reference[i])
		if (str[i] > reference[i])
			return (1);
	return (0);
}

int	check_long_pos(char *str)
{
	int		i;
	char	*reference;

	i = -1;
	if (str[0] == '+')
		reference = "+9223372036854775807";
	else
		reference = "9223372036854775807";
	while (str[++i] && reference[i])
		if (str[i] > reference[i])
			return (1);
	return (0);
}

int	ft_long(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[0] == '-' || str[0] == '+')
		i--;
	if (i < 19)
		return (0);
	if (i > 19)
		return (1);
	if (str[0] == '-')
		return (check_long_neg(str));
	else
		return (check_long_pos(str));
}

int	ft_num(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (1);
	return (0);
}

void	ft_exit(t_data *data)
{
	int	code;

	code = 0;
	if (data->pid != 0)
		printf("exit\n");
	if (data->args[1] && (ft_num(data->args[1]) || ft_long(data->args[1])))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(data->args[1], 2);
		ft_putstr_fd(" :numeric argument required\n", 2);
		clean_exit(data, set_err_status(2));
	}
	if (data->args[1] && data->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_var.g_status = 1;
		return ;
	}
	if (data->args[1])
		code = ft_atoi(data->args[1]);
	if (code > 255)
		code = code % 256;
	clean_exit(data, set_err_status(code));
}
