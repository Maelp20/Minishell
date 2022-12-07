/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:53:33 by mpignet           #+#    #+#             */
/*   Updated: 2022/12/07 16:05:49 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* Displaying env : var[0] contains "VarName=" and var[1] its value. */

void	ft_env(t_data *data)
{
	t_envp	*first_node;

	first_node = data->envp;
	if (!data->envp)
		return ;
	while (data->envp)
	{
		printf("%s", data->envp->var[0]);
		printf("%s\n", data->envp->var[1]);
		data->envp = data->envp->next;
	}
	data->envp = first_node;
}