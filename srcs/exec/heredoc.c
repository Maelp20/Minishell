/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:55:00 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/27 22:46:30 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	handle_signal_hd(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_var.g_stop = 1;
		g_var.g_status = 130;
	}
	if (signal == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 0);
}

void	signal_heredoc_handler(void)
{
	struct sigaction	s_sig;
	struct sigaction	sa;

	s_sig.sa_sigaction = &handle_signal_hd;
	s_sig.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sig.sa_mask);
	sigaction(SIGINT, &s_sig, 0);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

int	setup_heredoc(t_data *data)
{
	int	fd;

	signal_heredoc_handler();
	fd = open("/tmp/.heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		clean_exit(data, 1);
	return (fd);
}

void	ft_heredoc(t_data *data)
{
	int		tmp_fd;
	int		stdin_fd;
	char	*line;

	if (g_var.g_stop == 1)
		return ;
	tmp_fd = setup_heredoc(data);
	stdin_fd = dup(STDIN_FILENO);
	ft_putstr_fd("> ", 1);
	line = get_next_line(stdin_fd);
	while (line)
	{
		if (!ft_strncmp(line, data->is_heredoc, ft_strlen(data->is_heredoc))
			&& ft_strlen(data->is_heredoc) + 1 == ft_strlen(line))
			break ;
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(line, tmp_fd);
		free(line);
		line = get_next_line(stdin_fd);
	}
	if (line)
		free(line);
	close (stdin_fd);
	close (tmp_fd);
	setup_sigint_handler();
}
