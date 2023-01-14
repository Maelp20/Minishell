/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:08:37 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/14 17:42:20 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_create_infile(t_data *data)
{
	int		tmp_fd;
	int		stdin_fd;
	char	*line;

	tmp_fd = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		exit_error("heredoc", data);
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
}

void	ft_open_infile(t_data *data)
{
	if (data->is_heredoc)
	{
		data->in_fd = open(".heredoc.tmp", O_RDONLY);
		if (data->in_fd < 0)
			perror("infile");
	}
	else
	{
		data->in_fd = open(data->infile, O_RDONLY);
		if (data->in_fd < 0)
			perror("infile");
	}
}

void	ft_open_outfile(t_data *data)
{
	if (data->is_append)
	{
		data->out_fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->out_fd < 0)
			perror("outfile");
	}
	else
	{
		data->out_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->out_fd < 0)
			perror("outfile");
	}
}