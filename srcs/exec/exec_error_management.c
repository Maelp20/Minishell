/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:20:41 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/13 16:10:42 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_wait(t_data *data)
{
	int	status;

	(void)data;
	while (wait(&status) != -1)
    {
		// waitpid(data->pid, &status, 0);
        // data = data->next;
		continue;
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

void	ft_free_close(t_data *data)
{
	printf("frees\n");
	if (data->args)
		ft_free_dble_array((void **)data->args);
	if (data->env)
		ft_free_dble_array((void **)data->env);
	while (data->envp)
    {
		ft_free_dble_array((void **)data->envp->var);
        data->envp = data->envp->next;
    }
	printf("frees2\n");
	if (data->cmd_path)
		free(data->cmd_path);
	if (data->in_fd > -1)
		close(data->in_fd);
	if (data->out_fd > -1)
		close(data->out_fd);
	printf("frees3\n");
}

/* void	ft_close_pipes(t_data *data)
{
	while(data)
	{
		if (data->fds->pipe[0] > -1)
			if (close(data->fds->pipe[0]) == -1)
				perror("close");
		if (data->fds->pipe[1] > -1)
			if (close(data->fds->pipe[1]) == -1)
				perror("close");
		data = data->next;
	}
}

void	ft_close_fds(t_data *data)
{
	if (data->in_fd != -1)
		close (data->in_fd);
	if (data->out_fd != -1)
		close (data->out_fd);
	data = data->next;
	ft_close_pipes(data);
} */

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