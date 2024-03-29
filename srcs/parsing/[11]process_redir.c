/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [11]process_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:24:09 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/31 13:21:01 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	process_node_redir(t_tok *node, t_tok **lst)
{
	t_tok	*temp;
	t_tok	*temp2;

	if (ft_strcmp(node->token, (*lst)->token))
	{
		temp = (*lst)->next;
		tok_del_one(*lst);
		*lst = temp;
		temp = (*lst)->next;
		tok_del_one(*lst);
		*lst = temp;
		return ;
	}
	temp = *lst;
	while (!ft_strcmp(temp->next->token, node->token))
		temp = temp->next;
	temp2 = temp->next->next;
	tok_del_one(temp->next);
	temp->next = temp2;
	if (temp->next->next)
		temp2 = temp->next->next;
	else
		temp2 = NULL;
	tok_del_one(temp->next);
	temp->next = temp2;
}

void	process_redir(t_tok **lst, t_data **data)
{
	t_tok	*temp_tok;

	temp_tok = *lst;
	while (lst && temp_tok && !ft_strcmp(temp_tok->token, "|"))
	{
		if (lst && check_redir(lst, &temp_tok, data, *data))
			temp_tok = *lst;
		else
			temp_tok = temp_tok->next;
	}
}

int	check_out_file(char *str, t_data *node, t_tok **lst, t_data **data)
{
	int	fd;

	stat(str, &node->path_stat);
	if (S_ISDIR(node->path_stat.st_mode))
	{
		free_structures(lst, data);
		return (0);
	}
	fd = open(str, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		free_structures(lst, data);
		return (0);
	}
	close(fd);
	return (1);
}

int	check_in_file(char *str, t_data *node, t_tok **lst, t_data **data)
{
	int	fd;

	stat(str, &node->path_stat);
	if (S_ISDIR(node->path_stat.st_mode))
	{
		free_structures(lst, data);
		return (0);
	}
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		free_structures(lst, data);
		return (0);
	}
	close(fd);
	return (1);
}

void	free_structures(t_tok **lst, t_data **data)
{
	(void)data;
	ft_free_tok(lst);
	lst = NULL;
}
