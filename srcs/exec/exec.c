/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:05 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/13 17:11:04 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* static void	close_all_pipe(t_data *data)
{
	if (data->in_fd)
		close(data->in_fd);
	if (data->out_fd)
		close(data->out_fd);
	data = data->next;
	while (data)
	{
		close(data->fds->pipe[0]);
		close(data->fds->pipe[1]);
		data = data->next;
	}
} */

void	ft_close_pipes(t_data *data)
{
	data = data->next;
	while(data)
	{
		if (data->fds->pipe[0] != -1)
			if (close(data->fds->pipe[0]) == -1)
				perror("close");
		if (data->fds->pipe[1] != -1)
			if (close(data->fds->pipe[1]) == -1)
				perror("close");
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

static void	do_dups(t_data *data)
{
	if (data->in_pipe || data->infile)
	{
		if (dup2(data->in_fd, STDIN_FILENO) == -1)
		{
			ft_close_fds(data);
			exit_error("dup2", data);
		}
		close (data->fds->pipe[1]);
		data->fds->pipe[1] = -1;
		close(data->in_fd);
	}
	if (data->out_pipe || data->outfile)
	{
		if (dup2(data->out_fd, STDOUT_FILENO) == -1)
		{
			ft_close_fds(data);
			exit_error("dup2", data);
		}
		close (data->next->fds->pipe[0]);
		data->next->fds->pipe[0] = -1;
		close(data->out_fd);
	}
	//close (data->fds->pipe[0]);
	//close_all_pipe(data);
}

static void	redirect_fds(t_data *data)
{
	if (data->infile)
		ft_open_infile(data);
	if (data->outfile)
		ft_open_outfile(data);
	//printf("cmd : %s, in : %d / out : %d\n", data->args[0], data->in_fd, data->out_fd);
	do_dups(data);
}

/* static void	redirect_fds(t_data *data)
{
	if (data->infile)
	{
		ft_open_infile(data);
		dup2(data->in_fd, STDIN_FILENO);
		close(data->in_fd);
	}
	else if (data->in_pipe)
	{
		dup2(data->fds->pipe[0], STDIN_FILENO);
		close (data->fds->pipe[0]);
	}
	if (data->outfile)
	{
		ft_open_outfile(data);
		dup2(data->out_fd, STDOUT_FILENO);
		close(data->out_fd);
	}
	else if (data->out_pipe)
	{
		dup2(data->next->fds->pipe[1], STDIN_FILENO);
		close (data->next->fds->pipe[1]);
	}
	printf("cmd : %s, in : %d / out : %d\n", data->args[0], data->in_fd, data->out_fd);
	//do_dups(data);
	//close_all_pipe(data);
} */

void	exec_builtin(t_data *data)
{
	ft_putstr_fd("Exec builtin\n", 2);
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

static void	child(t_data *data, t_data *first_node)
{
	printf("pid = %d\n", data->pid);
	redirect_fds(data);
	ft_close_pipes(first_node);
	if (data->is_builtin)
	{
		exec_builtin(data);
		exit (EXIT_SUCCESS);
	}
	else
	{
		if (ft_strchr(data->args[0], '/'))
		{
			if (access(data->args[0], F_OK | X_OK) != 0)
				exit_error("access", data);
			if(execve(data->args[0], data->args, data->env) == -1)
				perror("execve");
			exit_error("execve", data);
		}
		data->cmd_path = ft_get_path(data);
		if (execve(data->cmd_path, data->args, data->env) == -1)
			perror("execve");
		exit_error("execve", data);
	}
}

/* 
Special condition : if there is only one command and its a builtin, we need to execute it in the parent and not a child. 
This is to reproduce bash behaviour, where a single builtin call can modify environment variables in parent for example.
The rest of execution is pretty much like pipex except for the in and outs management, 
since at all times it can be a heredoc, a file or a pipe.
 */

int	init_pipes(t_data *data)
{
	t_data *first_node;

	first_node = data;
	while (data)
	{
		if (data->in_pipe)
		{			
			data->fds = malloc (sizeof(t_pipes));
			if (!data->fds)
				return (perror("malloc"), 1);
			if (pipe(data->fds->pipe) == -1)
				return (perror("pipe"), 1);
		}
		data = data->next;
	}
	data = first_node;
	while (data)
	{
		if (data->in_pipe)
		{
			data->in_fd = data->fds->pipe[0];
		}
		if(data->out_pipe)
		{			
			data->out_fd = data->next->fds->pipe[1];
		}
		data = data->next;
	}
	return (0);
}

int ft_exec(t_data *data)
{
	t_data	*first_node;

	first_node = data;
	if (ft_data_size(data) == 1 && data->is_builtin)
		exec_builtin(data);
	else
	{
		if (init_pipes(data))
			return (1);
		while (data)
		{
			data->pid = fork();
			if (data->pid == -1)
			{
				ft_close_fds(data);
				exit_error("Fork", data);
			}
			else if (data->pid == 0)
			{
				child(data, first_node);
				ft_close_fds(data);
				//data = data->next;
			}
			if (data->is_heredoc)
				unlink(".heredoc.tmp");
			data = data->next;
		}
		data = first_node;
		ft_close_pipes(data);
		//ft_free_close(data);
		ft_wait(data);
	}
	return (0);
}




/* int main (int ac, char **av, char **envp)
{
	t_data	*data;
	t_data	*first_node;
	t_envp	*envi;

	(void)ac;
	(void)av;
	envi = get_env(envp);
	data = malloc (sizeof(t_data));
	first_node = data;
	data->envp = envi;
	data->fds = malloc (sizeof(t_pipes));
	if (pipe(data->fds->pipe) == -1)
		perror("pipe");
	data->args = malloc (sizeof(char **) * 3);
	data->args[0] = "echo";
	data->args[1] = "lol";
	data->args[2] = NULL;
	data->in_fd = 0;
	data->out_fd = 0;
	data->is_builtin = 1;
	data->infile = NULL;
	data->outfile = NULL;
	data->in_pipe = 0;
	data->out_pipe = 1;
	data->next = malloc (sizeof(t_data));
	data = data->next;
	data->envp = envi;
	data->args = malloc (sizeof(char **) * 3);
	data->fds = malloc (sizeof(t_pipes));
	if (pipe(data->fds->pipe) == -1)
		perror("pipe");
	data->args[0] = "wc";
	data->args[1] = NULL;
	data->args[2] = NULL;
	data->in_fd = 0;
	data->out_fd = 0;
	data->is_builtin = 0;
	data->infile = NULL;
	data->outfile = NULL;
	data->in_pipe = 1;
	data->out_pipe = 0;
	data->cmd_path = "/usr/bin/wc";
	data->is_builtin = 0;
	data->next = NULL;
	data = first_node;
	ft_exec(data);
	return (0);
} */