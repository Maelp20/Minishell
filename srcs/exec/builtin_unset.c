/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:10:01 by mpignet           #+#    #+#             */
/*   Updated: 2022/12/07 15:58:57 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_unset(t_data *data)
{
	char	*var;
	t_envp	*first_node;

	if (!data->envp || !data->args[1])
		return (1);
	var = ft_strjoin(data->args[1], "=");
	first_node = data->envp;
	while (data->envp->next->var)
	{
		printf("data var : %s\n", data->envp->next->var[0]);
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