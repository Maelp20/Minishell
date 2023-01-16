/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:20:41 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/16 17:10:20 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_close_pipes(t_data *data)
{
	data = data->next;
	while(data)
	{
		close(data->fds->pipe[0]);
		close(data->fds->pipe[1]);
		
		data = data->next;
	}
}

void	ft_close_fds(t_data *data)
{
	if (data->in_fd != -1)
		if (close (data->in_fd) == -1)
			perror("close");
	if (data->out_fd != -1)
		if (close (data->out_fd) == -1)
			perror("close");
	data = data->next;
	ft_close_pipes(data);
}

void	ft_wait(t_data *data)
{
	int	status;

	(void)data;
	while (wait(&status) != -1)
		continue;
}

void	ft_free_dble_array(void **tab)
{
	int	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	ft_free(t_data *data)
{
	if (data->args)
		ft_free_dble_array((void **)data->args);
	if (data->env)
		ft_free_dble_array((void **)data->env);
	ft_envpclear(&(data->envp));
	if (data->fds)
		free(data->fds);
	if (data->cmd_path)
		free(data->cmd_path);
	if (data->is_heredoc)
		free(data->is_heredoc);
	if (data->infile)
		free(data->infile);
	if (data->outfile)
		free(data->outfile);
}

void	clean_exit(t_data *data, int err)
{
    while (data)
    {
        ft_free(data);
		//free(data);
        data = data->next;  
    }
	exit (err);
}