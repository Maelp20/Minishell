/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:05 by mpignet           #+#    #+#             */
/*   Updated: 2022/12/06 16:29:26 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	do_dups(t_data *data)
{
	if (data->in_fd > -1)
	{
		if (dup2(data->in_fd, STDIN_FILENO) == -1)
		{
			// ft_close_fds(data);
			// exit_error("dup2", data);
		}		
	}
	if (data->out_fd > -1)
	{
		if (dup2(data->out_fd, STDOUT_FILENO) == -1)
		{
			// ft_close_fds(data);
			// exit_error("dup2", data);
		}
	}
}

static void	redirect_fds(t_data *data)
{
	if (data->infile)
		ft_open_infile(data);
	else if (data->in_pipe)
		data->in_fd = data->fds->pipe1[0];
	if (data->outfile)
		ft_open_outfile(data);
	else if(data->out_pipe)
		data->out_fd = data->fds->pipe2[1];
	do_dups(data);
	// ft_close_fds(data);
}

void	exec_builtin(t_data *data)
{
	ft_printf("exec builtin\n");
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
			// if (access(data->args[0], F_OK | X_OK) != 0)
			// 	exit_error("access", data);
			execve(data->args[0], data->args, data->envp->var);
			// exit_error("execve", data);
		}
		execve(data->cmd_path, data->args, data->envp->var);
		// exit_error("execve", data);
	}
}

/* 
Special condition : if there is only one command and its a builtin, we need to execute it in the parent and not a child. 
This is to reproduce bash behaviour, where a single builtin call can modify environment variables in parent for example.

The rest of execution is pretty much like pipex except for the in and outs management, 
since at all times it can be a heredoc, a file or a pipe.
 */

int ft_exec(t_data *data)
{
	if (ft_data_size(data) == 1 && data->is_builtin)
		exec_builtin(data);
	else
	{		
		while (data)
		{
			data->pid = fork();
			// if (data->pid == -1)
			// {
			// 	ft_close_fds(&data);
			// 	exit_error("Fork", &data);
			// }
			if (data->pid == 0)
				child(data);
			// if (data->is_heredoc)
			// 	unlink(".heredoc.tmp");
			data = data->next;
		}
		// ft_close_pipes(data);
		// ft_free_close(data);
		// ft_wait(data);
	}
	while (data->envp)
	{
		printf("%s", data->envp->var[0]);
		printf("%s\n", data->envp->var[1]);
		data->envp = data->envp->next;
	}
	return (0);
}