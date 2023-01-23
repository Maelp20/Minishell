/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:53:33 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/23 18:59:19 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* Displaying env : var[0] contains "VarName=" and var[1] its value. */

void	ft_env(t_data *data)
{
	t_envp	*first_node;

	g_var.g_status = 0;
	if (!data->envp)
		return ;
	if (data->args[1])
	{
		ft_putstr_fd("minishell: env: no options or arguments allowed\n", 2);
		g_var.g_status = 127;
		return ;
	}
	first_node = data->envp;
	while (data->envp)
	{
		if (data->envp->var[1] != NULL)
		{
			printf("%s", data->envp->var[0]);
			printf("%s\n", data->envp->var[1]);
		}
		data->envp = data->envp->next;
	}
	data->envp = first_node;
}
