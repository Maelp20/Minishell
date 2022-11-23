/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:10:01 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/23 11:54:24 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_unset(t_data *data)
{
	int		found;
	
	found = 0;
	if (!data->envp)
		return (1);
	while (data->envp->var)
	{
		if (ft_strnstr(data->envp->var[0], data->args[1], ft_strlen(data->args[1])))
		{
			found = 1;
			break ;
		}
		data->envp = data->envp->next;
	}
	if (found)
	{		
		free(data->envp->var[0]);
		free(data->envp->var[1]);
	}
	return (0);
}