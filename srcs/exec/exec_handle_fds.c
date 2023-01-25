/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_fds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:22:37 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/25 20:39:07 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_close_pipes(t_data *data)
{
	data = data->next;
	while (data)
	{
		if (data->in_pipe)
		{
			if (data->in_pipe)
			{		
				close(data->fds->pipe[0]);
				close(data->fds->pipe[1]);
			}	
		}
		data = data->next;
	}
}

void	ft_close_fds(t_data *data)
{
	if (data->in_fd != -1)
	{
		if (close (data->in_fd) == -1)
			perror("close");
	}
	if (data->out_fd != -1)
	{
		if (close (data->out_fd) == -1)
			perror("close");
	}
	data = data->next;
	ft_close_pipes(data);
}

static void	do_dups(t_data *data)
{
	if (data->in_pipe || data->infile || data->is_heredoc)
	{
		if (dup2(data->in_fd, STDIN_FILENO) == -1)
		{
			ft_close_fds(data);
			clean_exit(data, set_err_status(errno));
		}
		if (data->in_pipe)
			close(data->fds->pipe[1]);
		close(data->in_fd);
	}
	if (data->out_pipe || data->outfile)
	{
		if (dup2(data->out_fd, STDOUT_FILENO) == -1)
		{
			ft_close_fds(data);
			clean_exit(data, set_err_status(errno));
		}
		if (data->out_pipe)
			close (data->next->fds->pipe[0]);
		close(data->out_fd);
	}
}

int	redirect_fds(t_data *data)
{
	if (data->infile || data->is_heredoc)
		if (ft_open_infile(data))
			return (1);
	if (data->outfile)
		if (ft_open_outfile(data))
			return (1);
	do_dups(data);
	return (0);
}

int	init_pipes(t_data *data)
{
	t_data	*first_node;

	first_node = data;
	while (data)
	{
		if (data->in_pipe)
		{			
			data->fds = malloc (sizeof(t_pipes));
			if (!data->fds)
				return (perror("malloc"), set_err_status(1));
			if (pipe(data->fds->pipe) == -1)
				return (perror("pipe"), set_err_status(1));
		}
		data = data->next;
	}
	data = first_node;
	while (data)
	{
		if (data->in_pipe)
			data->in_fd = data->fds->pipe[0];
		if (data->out_pipe)
			data->out_fd = data->next->fds->pipe[1];
		data = data->next;
	}
	return (0);
}
