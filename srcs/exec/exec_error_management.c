/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:20:41 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/19 14:54:37 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void print_tout_huehue(t_data **data);

void	msg_no_such_file(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	msg_cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

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

void	ft_free_data(t_data *data)
{
	//print_tout_huehue(&data);
	t_data	*tmp;

    while (data)
    {
		tmp = data;
		data = data->next;
		if (tmp->args)
			ft_free_dble_array((void **)tmp->args);
		if (tmp->env)
			ft_free_dble_array((void **)tmp->env);
		ft_envpclear(&(tmp->envp));
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
	//printf("Clean exit\n");
    ft_free_data(data);
	rl_clear_history();
	exit (err);
}