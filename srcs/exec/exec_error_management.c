/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:20:41 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/23 21:09:45 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_tout_huehue(t_data **data);

int	set_err_status(int nb)
{
	g_var.g_status = nb;
	return (g_var.g_status);
}

void	ft_close_pipes(t_data *data)
{
	data = data->next;
	while (data)
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
	{
		g_var.g_status = WEXITSTATUS(status);
		continue ;
	}
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

void	ft_free_data(t_data *data)
{
	t_data	*tmp;

	while (data)
	{
		tmp = data;
		data = data->next;
		if (tmp->args)
			ft_free_dble_array((void **)tmp->args);
		if (tmp->env)
		{
			ft_free_dble_array((void **)tmp->env);
			tmp->envp = NULL;
		}
		if (tmp->fds)
			free(tmp->fds);
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		if (tmp->is_heredoc)
			free(tmp->is_heredoc);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		free(tmp);
	}
}

void	clean_exit(t_data *data, int err)
{
	if (data->envp)
		ft_envpclear(&(data->envp));
	ft_free_data(data);
	rl_clear_history();
	exit(err);
}

int	check_if_dir(char *path)
{
	struct stat	path_stat;
	
	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}