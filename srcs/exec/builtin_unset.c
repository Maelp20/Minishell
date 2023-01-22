/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:10:01 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/22 17:33:01 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_unset(t_data *data)
{
	char	*var;
	t_envp	*first_node;
	t_envp	*tmp;

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
			tmp = data->envp->next;
			ft_free_dble_array((void **)data->envp->next->var);
			data->envp->next = data->envp->next->next;
			free(tmp);
			break ;
		}
		data->envp = data->envp->next;
	}
	data->envp = first_node;
	return (free(var), 0);
}