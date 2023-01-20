/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:32:55 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/20 18:16:13 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* pour EXIT builtin :
	ATTENTION : la valeur de retour sera entre 0 et 255. exit doit tout nettoyer (free et close).
 */

int	ft_numeric(char *str)
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
	printf("exit\n");
	if (data->args[1] && ft_numeric(data->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(data->args[1], 2);
		ft_putstr_fd(" :numeric argument required\n", 2);
		clean_exit(data, set_err_status(1));
	}
	if (data->args[1] && data->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		err_status = 1;
		return ;
	}
	if (data->args[1])
		code = ft_atoi(data->args[1]);
	if (code > 255)
	{
		code = code % 256;
		clean_exit(data, set_err_status(code));
	}
	clean_exit(data, set_err_status(code));
}