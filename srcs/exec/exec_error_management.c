/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:20:41 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/23 12:47:08 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_wait(t_data *data)
{
	int	status;

	while (data)
    {
        waitpid(data->pid, &status, 0);
        data = data->next;
    }
}

void	ft_free_dble_array(void **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	ft_close_pipes(t_data *data)
{
	while (data)
	{	
		// if (data->pipefd[i][0] > -1)
		// 	close(data->pipefd[i][0]);
		// if (data->pipefd[i][1] > -1)
		// 	close(data->pipefd[i][1]);
		data = data->next;
	}
}

void	ft_free_close(t_data *data)
{
	if (data->args)
		ft_free_dble_array((void **)data->args);
	while (data->envp)
    {
		ft_free_dble_array((void **)data->envp->var);
        data->envp = data->envp->next;
    }
	if (data->cmd_path)
		free(data->cmd_path);
	if (data->in_fd > -1)
		close(data->in_fd);
	if (data->out_fd > -1)
		close(data->out_fd);
}

void	ft_close_fds(t_data *data)
{
	if (data->in_fd != -1)
		close (data->in_fd);
	if (data->out_fd != -1)
		close (data->out_fd);
	ft_close_pipes(data);
}

void	exit_error(char *err, t_data *data)
{
    while (data)
    {
        ft_free_close(data);
        data = data->next;  
    }
    if (err)
	{
        if (!ft_strncmp(err, "dup2", 5))
            exit(1);
        else if (!ft_strncmp(err, "malloc", 7))
            exit(2);
        else if (!ft_strncmp(err, "access", 7))
            exit(3);
        else if (!ft_strncmp(err, "execve", 7))
            exit(4);
        else if (!ft_strncmp(err, "heredoc", 9))
            exit (5);
    }
    else
        perror(err);
}