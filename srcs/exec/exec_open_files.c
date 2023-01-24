/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:08:37 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/24 19:34:24 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_heredoc(t_data *data)
{
	int		tmp_fd;
	int		stdin_fd;
	char	*line;
	
	tmp_fd = open("/tmp/.heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		clean_exit(data, 1);
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

int	ft_open_infile(t_data *data)
{
	if (data->is_heredoc)
	{
		data->in_fd = open("/tmp/.heredoc.tmp", O_RDONLY);
		if (data->in_fd < 0)
			return (perror("heredoc"), 1);
	}
	else
	{
		if (check_if_dir(data->infile, data))
			return (msg_is_directory(data->infile), 1);
		data->in_fd = open(data->infile, O_RDONLY);
		if (data->in_fd < 0)
			return (perror(data->infile), set_err_status(errno), 1);
	}
	return (0);
}

int	ft_open_outfile(t_data *data)
{
	if (data->is_append)
	{
		data->out_fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->out_fd < 0)
			return (perror(data->outfile), set_err_status(errno), 1);
	}
	else
	{
		if (check_if_dir(data->outfile, data))
			return (msg_is_directory(data->outfile), 1);
		data->out_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->out_fd < 0)
			return (perror(data->outfile), set_err_status(errno), 1);
	}
	return (0);
}