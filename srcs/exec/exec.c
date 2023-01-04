/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:05 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/04 15:29:21 by mpignet          ###   ########.fr       */
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
	printf("OUT FD = %d\n", data->out_fd);
}

static void	redirect_fds(t_data *data)
{
	data->infile = 0;
	data->outfile = 0;
	data->in_fd = 0;
	data->out_fd = 0;
	if (pipe(data->fds->pipe1) == -1)
		perror ("pipe");
	if (data->infile)
		ft_open_infile(data);
	else if (data->in_pipe)
		data->in_fd = data->fds->pipe1[0];
	if (data->outfile)
		ft_open_outfile(data);
	else if(data->out_pipe)
		data->out_fd = data->fds->pipe1[1];
	do_dups(data);
	// ft_close_fds(data);
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
			printf("exec?\n");
			// if (access(data->args[0], F_OK | X_OK) != 0)
			// 	exit_error("access", data);
			if(execve(data->args[0], data->args, data->envp->var) == -1)
				perror("execve");
			// exit_error("execve", data);
		}
		printf("exec1?\n");
		if (execve(data->cmd_path, data->args, data->envp->var) == -1)
			perror("execve");
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
	{
		// printf("if\n");
		exec_builtin(data);
	}
	else
	{
		while (data)
		{
			printf("while\n");
			// printf("while\n");
			// printf("data->args[0] : %s\n", data->args[0]);
			if (data->is_builtin)
			{
				printf("bultin\n");
				// printf("is bultin\n");
				exec_builtin(data);
			}
			else
			{
				// printf("not bultin\n");
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
			}
			data = data->next;
		}
		// ft_close_pipes(data);
		// ft_free_close(data);
		ft_wait(data);
	}
	// while (data->envp)
	// {
	// 	printf("%s", data->envp->var[0]);
	// 	printf("%s\n", data->envp->var[1]);
	// 	data->envp = data->envp->next;
	// }
	return (0);
}

int main (int ac, char **av, char **envp)
{
	t_data	*data;
	t_data	*first_node;

	(void)ac;
	(void)av;
	data = malloc (sizeof(t_data));
	data->fds = malloc (sizeof(t_pipes));
	get_env(envp, data);
	first_node = data;
	data->args = malloc (sizeof(char **) * 3);
	data->args[0] = "echo";
	data->args[1] = "lol";
	data->args[2] = NULL;
	data->is_builtin = 1;
	data->out_pipe = 1;
	data->next = malloc (sizeof(t_data));
	data = data->next;
	get_env(envp, data);
	data->args = malloc (sizeof(char **) * 3);
	data->fds = malloc (sizeof(t_pipes));
	data->args[0] = "/usr/bin/wc";
	data->args[1] = NULL;
	data->args[2] = NULL;
	data->in_pipe = 1;
	data->cmd_path = "/usr/bin/wc/";
	data->is_builtin = 0;
	data->next = NULL;
	// data = data->next;
	// data->args = malloc (sizeof(char **) * 3);
	// data->args[0] = "grep";
	// data->args[1] = "o";
	// data->args[2] = NULL;
	// data->is_builtin = 1;
	// data = data->next;
	data = first_node;
	ft_exec(data);
	// free(data);
	return (0);
}