/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:05 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/27 22:39:55 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	exec_builtin(t_data *data)
{
	int	len;

	len = ft_strlen(data->args[0]);
	if (!ft_strncmp(data->args[0], "cd", len))
		ft_cd(data);
	else if (!ft_strncmp(data->args[0], "echo", len))
		ft_echo(data);
	else if (!ft_strncmp(data->args[0], "env", len))
		ft_env(data);
	else if (!ft_strncmp(data->args[0], "exit", len))
		ft_exit(data);
	else if (!ft_strncmp(data->args[0], "export", len))
		ft_export(data);
	else if (!ft_strncmp(data->args[0], "pwd", len))
		ft_pwd(data);
	else if (!ft_strncmp(data->args[0], "unset", len))
		ft_unset(data);
}

static void	exec_path_given(t_data *data, t_data *first_node)
{
	if (check_if_dir(data->args[0], data))
	{
		msg_is_directory(data->args[0]);
		clean_exit(first_node, g_var.g_status);
	}
	if (access(data->args[0], F_OK | X_OK) != 0)
	{
		msg_perror(data->args[0]);
		clean_exit(first_node, g_var.g_status);
	}
	if (execve(data->args[0], data->args, data->env) == -1)
		msg_perror(data->args[0]);
	clean_exit(first_node, g_var.g_status);
}

static void	child(t_data *data, t_data *first_node)
{
	if (redirect_fds(data) || g_var.g_stop == 1)
		clean_exit(first_node, g_var.g_status);
	setup_sig_child();
	ft_close_pipes(first_node);
	if (data->is_builtin)
	{
		exec_builtin(data);
		clean_exit(first_node, g_var.g_status);
	}
	else
	{
		if (ft_strchr(data->args[0], '/'))
			exec_path_given(data, first_node);
		data->cmd_path = ft_get_path(data);
		if (!data->cmd_path)
			clean_exit(first_node, g_var.g_status);
		if (execve(data->cmd_path, data->args, data->env) == -1)
			msg_perror(data->args[0]);
		clean_exit(first_node, g_var.g_status);
	}
}

static void	exec_fork(t_data *data, t_data *first_node)
{
	data->pid = fork();
	if (data->pid == -1)
	{
		ft_close_fds(data);
		clean_exit(first_node, set_err_status(errno));
	}
	else if (data->pid == 0)
		child(data, first_node);
	else if (data->pid > 0)
		sig_ignore_all();
}

int	ft_exec(t_data *data)
{
	t_data	*first_node;

	if (!data->args)
		return (ft_free_data(data), g_var.g_status);
	first_node = data;
	data->pid = -2;
	if (ft_data_size(data) == 1 && data->is_builtin && !data->outfile
		&& !data->infile && !data->is_heredoc)
		exec_builtin(data);
	else
	{
		if (init_pipes(data))
			clean_exit(data, g_var.g_status);
		while (data)
		{
			exec_fork(data, first_node);
			data = data->next;
		}
		data = first_node;
		ft_close_pipes(data);
		ft_wait(data);
	}
	ft_free_data(data);
	return (g_var.g_status);
}
