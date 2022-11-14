/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:05 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/14 18:28:23 by mpignet          ###   ########.fr       */
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
		data = data->next;
		nb++;
	}
	return (nb);
}

int exec(t_data *data)
{
	int	nb_cmds;

	nb_cmds = ft_data_size(data);
	if (nb_cmds == 1 && data->is_builtin)
		return ;//exec builtin
	while (nb_cmds > 0)
	{
		d.pids[d.child] = fork();
		if (d.pids[d.child] == -1)
		{
			ft_close_fds(&d);
			exit_error("Fork", &d);
		}
		else if (d.pids[d.child] == 0)
			child(&d, av);
		d.child++;
	}
	ft_close_pipes(data);
	ft_free_close(data);
	ft_wait(data);
	return (0);
}