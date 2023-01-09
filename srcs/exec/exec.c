/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:05 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/09 14:59:32 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	do_dups(t_data *data)
{
	if (data->in_pipe || data->infile)
	{
		if (dup2(data->in_fd, STDIN_FILENO) == -1)
		{
			// ft_close_fds(data);
			// exit_error("dup2", data);
		}
		close(data->fds->pipe[1]);
		close(data->in_fd);
	}
	if (data->out_pipe || data->outfile)
	{
		if (dup2(data->out_fd, STDOUT_FILENO) == -1)
		{
			// ft_close_fds(data);
			// exit_error("dup2", data);
		}
		close(data->next->fds->pipe[0]);
		close(data->out_fd);
	}
	ft_close_fds(data);
}

static void	redirect_fds(t_data *data)
{
	data->infile = 0;
	data->outfile = 0;
	data->in_fd = 0;
	data->out_fd = 1;
	if (data->infile)
		ft_open_infile(data);
	else if (data->in_pipe)
	{
		//printf("in pipe : %d\n", data->fds->pipe[0]);
		data->in_fd = data->fds->pipe[0];
	}
	if (data->outfile)
		ft_open_outfile(data);
	else if(data->out_pipe)
	{
		data->out_fd = data->next->fds->pipe[1];
		//printf("out pipe : %d\n", data->next->fds->pipe[1]);
	}
	// printf("in fd : %d\n", data->in_fd);
	// printf("out fd : %d\n", data->out_fd);
	do_dups(data);
	//ft_close_fds(data);
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
			if(execve(data->args[0], data->args, data->envp->var) == -1)
				perror("execve");
			exit_error("execve", data);
		}
		if (execve(data->cmd_path, data->args, data->envp->var) == -1)
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

int ft_exec(t_data *data)
{
	if (ft_data_size(data) == 1 && data->is_builtin)
		exec_builtin(data);
	else
	{
		while (data)
		{
			if (data->out_pipe && data->next)
			{
				if (pipe(data->next->fds->pipe) == -1)
					perror ("pipe");
			}
			data->pid = fork();
			if (data->pid == -1)
			{
				ft_close_fds(data);
				exit_error("Fork", data);
			}
			if (data->pid == 0)
			{
				child(data);
				ft_close_fds(data);
			}
			if (data->is_heredoc)
				unlink(".heredoc.tmp");
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

/* int main (int ac, char **av, char **envp)
{
	t_data	*data;
	t_data	*first_node;

	(void)ac;
	(void)av;
	data = malloc (sizeof(t_data));
	get_env(envp, data);
	first_node = data;
	data->args = malloc (sizeof(char **) * 3);
	data->fds = malloc (sizeof(t_pipes));
	// if (pipe(data->fds->pipe) == -1)
	// 	perror ("pipe");
	data->args[0] = "echo";
	data->args[1] = "lol";
	data->args[2] = NULL;
	data->is_builtin = 1;
	data->in_pipe = 0;
	data->out_pipe = 1;
	data->next = malloc (sizeof(t_data));
	data = data->next;
	get_env(envp, data);
	data->args = malloc (sizeof(char **) * 3);
	data->fds = malloc (sizeof(t_pipes));
	// if (pipe(data->fds->pipe) == -1)
	// 	perror ("pipe");
	data->args[0] = "/usr/bin/wc";
	data->args[1] = NULL;
	data->args[2] = NULL;
	data->in_pipe = 1;
	data->out_pipe = 0;
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
} */




// OTHER WAY OF EXEC

/* static void	redirect_fds(t_data *data)
{
	printf("redirect fds\n");
	data->infile = 0;
	data->outfile = 0;
	data->in_fd = 0;
	data->out_fd = 1;
	if (data->infile)
		ft_open_infile(data);
	if (data->in_pipe)
		data->in_fd = data->fds->pipe[0];
	if (data->outfile)
		ft_open_outfile(data);
	else if(data->out_pipe)
		data->out_fd = data->next->fds->pipe[1];
	if (data->in_pipe && data->out_pipe)
	{
		if (dup2(data->fds->pipe[0], STDIN_FILENO) == -1)
		{
			ft_close_fds(data);
			exit_error("dup2", data);
		}
		if (dup2(data->next->fds->pipe[1], STDOUT_FILENO) == -1)
		{
			ft_close_fds(data);
			exit_error("dup2", data);
		}		
	}
	else
	{
		if (data->in_pipe)
		{
			if (dup2(data->fds->pipe[0], STDIN_FILENO) == -1)
			{
				ft_close_fds(data);
				exit_error("dup2", data);
			}
			close (data->fds->pipe[0]);
		}
		if (data->out_pipe)
		{
			if (dup2(data->next->fds->pipe[1], STDIN_FILENO) == -1)
			{
				ft_close_fds(data);
				exit_error("dup2", data);
			}
			close (data->next->fds->pipe[1]);
		}
	}
	// ft_close_fds(data);
}

void	exec_builtin(t_data *data)
{
	printf("going to exec bultin : %s\n", data->args[0]);
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
		printf("going to exec cmd : %s\n", data->args[0]);
		redirect_fds(data);
		if (ft_strchr(data->args[0], '/'))
		{
			ft_putstr_fd("exec?\n", 2);
			if (access(data->args[0], F_OK | X_OK) != 0)
				exit_error("access", data);
			if(execve(data->args[0], data->args, data->envp->var) == -1)
				perror("execve");
			exit_error("execve", data);
		}
		// call function to get_path of cmd (checking access for every PATH var path in env);
		if (execve(data->cmd_path, data->args, data->envp->var) == -1)
			perror("execve");
		exit_error("execve", data);
	}
}

int ft_exec_node(t_data *data)
{
	if (ft_data_size(data) == 1 && data->is_builtin)
		exec_builtin(data);
	else
	{
		data->pid = fork();
		if (data->pid == 0)
			child(data);
		// if (data->pid == -1)
		// {
		// 	ft_close_fds(&data);
		// 	exit_error("Fork", &data);
		// }
		if (data->is_heredoc)
			unlink(".heredoc.tmp");
		// ft_close_pipes(data);
		// ft_free_close(data);
		// ft_wait(data);
	}
	// while (data->envp)
	// {
	// 	printf("%s", data->envp->var[0]);
	// 	printf("%s\n", data->envp->var[1]);
	// 	data->envp = data->envp->next;
	// }
	return (0);
}

int ft_exec(t_data **data)
{
	t_data	*node;

	node = *data;
	while (node)
	{
		ft_exec_node(node);
		ft_close_pipes(node);
		node = node->next;
	}
	node = *data;
	ft_wait(node);
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
	if (pipe(data->fds->pipe) == -1)
		perror("pipe");
	get_env(envp, data);
	first_node = data;
	data->args = malloc (sizeof(char **) * 3);
	data->args[0] = "echo";
	data->args[1] = "lol";
	data->args[2] = NULL;
	data->is_builtin = 1;
	data->in_pipe = 0;
	data->out_pipe = 1;
	data->next = malloc (sizeof(t_data));
	data = data->next;
	get_env(envp, data);
	data->args = malloc (sizeof(char **) * 3);
	data->fds = malloc (sizeof(t_pipes));
	if (pipe(data->fds->pipe) == -1)
		perror("pipe");
	data->args[0] = "/usr/bin/wc";
	data->args[1] = NULL;
	data->args[2] = NULL;
	data->in_pipe = 1;
	data->out_pipe = 0;
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
	ft_exec(&data);
	// free(data);
	return (0);
} */