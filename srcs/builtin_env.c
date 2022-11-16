/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:53:33 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/16 16:03:41 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_env(t_data *data)
{
	if (!data->envp)
		return ;
	while (data->envp->var)
	{
		printf("%s", data->envp->var[0]);
		printf("%s\n", data->envp->var[1]);
		data->envp = data->envp->next;
	}
}