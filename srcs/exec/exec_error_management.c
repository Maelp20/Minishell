/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:20:41 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/29 00:25:46 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	set_err_status(int nb)
{
	g_var.g_status = nb;
	return (g_var.g_status);
}

void	ft_free_dble_array(void **tab)
{
	int	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
	{
		tab[i] = NULL;
		free(tab[i]);
	}
	tab = NULL;
	free(tab);
}

static void	ft_free_the_rest(t_data *tmp)
{
	if (tmp->fds)
		free(tmp->fds);
	if (tmp->cmd_path)
	{
		tmp->cmd_path = NULL;
		free(tmp->cmd_path);
	}
	if (tmp->is_heredoc)
	{
		tmp->is_heredoc = NULL;
		free(tmp->is_heredoc);
	}
	if (tmp->infile)
	{
		tmp->infile = NULL;
		free(tmp->infile);
	}
	if (tmp->outfile)
	{
		tmp->outfile = NULL;
		free(tmp->outfile);
	}
	if (tmp->is_heredoc)
		unlink("/tmp/.heredoc.tmp");
}

void	ft_free_data(t_data *data)
{
	t_data	*tmp;

	while (data)
	{
		tmp = data;
		data = data->next;
		if (tmp->args)
		{		
			ft_free_dble_array((void **)tmp->args);
			tmp->args = NULL;
		}
		if (tmp->env)
		{			
			ft_free_dble_array((void **)tmp->env);
			tmp->env = NULL;
		}
		ft_free_the_rest(tmp);
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
