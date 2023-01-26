/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:42:05 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/26 18:23:07 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_sigint_child(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_sig_child(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint_child;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	sig_ignore_all(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

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

/* 
Special condition : if there is only one command and its a builtin, we need to 
execute it in the parent and not a child. 
This is to reproduce bash behaviour, where a single builtin call can modify 
environment variables in parent for example.
The rest of execution is pretty much like pipex except for the in and outs 
management, since at all times it can be a heredoc, a file or a pipe.
*/

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

	g_var.g_status = 0;
	first_node = data;
	data->pid = -2;
	if (ft_data_size(data) == 1 && data->is_builtin && !data->outfile
		&& !data->infile && !data->is_heredoc)
		exec_builtin(data);
	else
	{
		if (init_pipes(data))
			return (g_var.g_status);
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
	// if (pipe(data->fds->pipe) == -1)
	// 	perror("pipe");
	data->args = malloc (sizeof(char **) * 3);
	data->args[0] = "cat";
	data->args[1] = NULL;
	data->args[2] = NULL;
	data->is_heredoc[0] = "lol";
	data->is_heredoc[0] = "hey";
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
	// if (pipe(data->fds->pipe) == -1)
	// 	perror("pipe");
	data->args[0] = "ls";
	data->args[1] = NULL;
	data->args[2] = NULL;
	data->in_fd = 0;
	data->out_fd = 0;
	data->is_builtin = 0;
	data->infile = NULL;
	data->outfile = NULL;
	data->in_pipe = 1;
	data->out_pipe = 0;
	data->cmd_path = "/usr/bin/ls";
	data->is_builtin = 0;
	data->next = NULL;
	data = first_node;
	ft_exec(data);
	return (0);
} */