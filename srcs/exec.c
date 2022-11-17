/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:05 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/17 17:42:46 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	do_dups(t_data *data, int in, int out)
{
	if (in)
	{
		if (dup2(in, STDIN_FILENO) == -1)
		{
			ft_close_fds(data);
			exit_error("dup2", data);
		}		
	}
	if(out)
	{
		if (dup2(out, STDOUT_FILENO) == -1)
		{
			ft_close_fds(data);
			exit_error("dup2", data);
		}
	}
}

static void	redirect_fds(t_data *data)
{
	int	in;
	int	out;
	
	if (data->in_pipe)
		in = data->fds->pipe1[0];
	else
		in = data->in_fd;
	if (data->out_pipe)
		out = data->fds->pipe2[1];
	else
		out = data->out_fd;
	do_dups(data, in, out);
	ft_close_fds(data);
}

void	exec_builtin(t_data *data)
{
	int	len;

	len = ft_strlen(data->args[0]);
	redirect_fds(data);
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

static void	child(t_data *data)
{
	if (data->is_builtin)
		exec_builtin(data);
	else
	{
		redirect_fds(data);
		if (ft_strchr(data->args[0], '/'))
		{
			if (access(data->args[0], F_OK | X_OK) != 0)
				exit_error("access", data);
			execve(data->args[0], data->args, data->envp);
			exit_error("execve", data);
		}
		execve(data->cmd_path, data->args, data->envp);
		exit_error("execve", data);		
	}

}

/* 
Special condition : if there is only one command and its a builtin, we need to execute it in the parent and not a child. 
This is to reproduce bash behaviour, where a single builtin call can modify environment variables in parent for example.

The rest of execution is pretty much like pipex except for the in and outs management, 
since at all times it can be a file or a pipe.
 */

int exec(t_data *data)
{
	if (ft_data_size(data) == 1 && data->is_builtin)
		exec_builtin(data);
	while (data)
	{
		data->pid = fork();
		if (data->pid == -1)
		{
			ft_close_fds(&data);
			exit_error("Fork", &data);
		}
		else if (data->pid == 0)
			child(&data);
		data = data->next;
	}
	ft_close_pipes(data);
	ft_free_close(data);
	ft_wait(data);
	return (0);
}