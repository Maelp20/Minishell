/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:10:01 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/20 16:21:48 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_unset(t_data *data)
{
	char	*var;
	t_envp	*first_node;

	err_status = 0;
	if (!data->envp || !data->args[1])
		return (1);
	var = ft_strjoin(data->args[1], "=");
	if (!var)
		return (perror("malloc"), set_err_status(1));
	first_node = data->envp;
	while (data->envp->next)
	{
		if (ft_strnstr(data->envp->next->var[0], var, ft_strlen(var)))
		{
			free(data->envp->next->var[0]);
			free(data->envp->next->var[1]);
			data->envp->next = data->envp->next->next;
			break ;
		}
		data->envp = data->envp->next;
	}
	data->envp = first_node;
	return (0);
}