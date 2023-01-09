/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:53:33 by mpignet           #+#    #+#             */
/*   Updated: 2022/12/13 15:20:08 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* Displaying env : var[0] contains "VarName=" and var[1] its value. */

void	ft_env(t_data *data)
{
	t_envp	*first_node;

	if (!data->envp)
		exit(EXIT_FAILURE);
	if (data->args[1])
	{
		ft_putstr_fd("env: no options or arguments allowed\n", 2);
		exit(EXIT_FAILURE);
	}
	first_node = data->envp;
	while (data->envp)
	{
		printf("%s", data->envp->var[0]);
		printf("%s\n", data->envp->var[1]);
		data->envp = data->envp->next;
	}
	data->envp = first_node;
}