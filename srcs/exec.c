/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:05 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/16 18:15:33 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_data_size(t_data *data)
{
	int	nb;

	if (!data)
		return (0);
	nb = 0;
	while (data)
	{
		nb++;
		data = data->next;
	}
	return (nb);
}

int exec(t_data *data)
{
	if (ft_data_size(data) == 1 && data->is_builtin)
		return ;//exec builtin
	while (data)
	{
		data->pid = fork();
		if (data->pid == -1)
		{
			ft_close_fds(&data);
			exit_error("Fork", &data);
		}
		else if (data->pid == 0)
			child(&data, data->args);
		data = data->next;
	}
	ft_close_pipes(data);
	ft_free_close(data);
	ft_wait(data);
	return (0);
}