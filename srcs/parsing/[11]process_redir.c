/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [11]process_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:24:09 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/30 09:17:36 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	process_redir(t_tok **lst, t_data **data)
{
	t_tok	*temp_tok;
	t_data	*temp_data;

	temp_tok = *lst;
	temp_data = *data;
	while (lst && temp_tok && !ft_strcmp(temp_tok->token, "|"))
	{
		if (lst && check_redir(lst, &temp_tok, data, temp_data))
			temp_tok = *lst;
		else
			temp_tok = temp_tok->next;
	}
}


void	check_out_file(char *str, t_data *node, t_tok **lst, t_data **data)
{
	int	fd;

	stat(str, &node->path_stat);
	if (S_ISDIR(node->path_stat.st_mode))
	{
		free_structures(lst, data);
		return ;
	}
	fd = open(str, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(str);
		free_structures(lst, data);
		return ;
	}
	close(fd);
}
void	check_in_file(char *str, t_data *node, t_tok **lst, t_data **data)
{
	int	fd;
	stat(str, &node->path_stat);
	if (S_ISDIR(node->path_stat.st_mode))
	{
		free_structures(lst, data);
		return ;
	}
	fd = open(str, O_RDONLY );
	if (fd == -1)
	{
		perror(str);
		free_structures(lst, data);
		return ;
	}
	close(fd);
}


void	free_structures(t_tok **lst, t_data **data)
{
	
	(void)data;
	ft_free_tok(lst);
	lst = NULL;;
}