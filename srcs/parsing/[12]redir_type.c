/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [12]redir_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:22:40 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/31 03:28:09 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	at_heredoc(t_tok *lst_node, t_data *d_node, t_tok **lst, t_data **data)
{
	if (d_node)
	{
		if (d_node->is_heredoc)
			free(d_node->is_heredoc);
		d_node->is_heredoc = ft_strdup(lst_node->next->token);
		if (!d_node->is_heredoc)
			clean_parsing(lst, data);
		ft_heredoc(d_node);
	}
	process_node_redir(lst_node, lst);
}

void	in_redir(t_tok *lst_node, t_data *d_node, t_tok **lst, t_data **data)
{
	if (d_node)
	{
		if (d_node->infile)
			free(d_node->infile);
		d_node->infile = ft_strdup(lst_node->next->token);
		if (!d_node->infile)
			clean_parsing(lst, data);
		if (check_in_file(d_node->infile, d_node, lst, data) == 0)
			return ;
	}
	process_node_redir(lst_node, lst);
}

void	out_redir(t_tok *lst_node, t_data *d_node, t_tok **lst, t_data **data)
{
	if (d_node)
	{
		if (d_node->outfile)
			free(d_node->outfile);
		d_node->outfile = ft_strdup(lst_node->next->token);
		if (!d_node->outfile)
			clean_parsing(lst, data);
		if (check_out_file(d_node->outfile, d_node, lst, data) == 0)
			return ;
	}
	process_node_redir(lst_node, lst);
}

void	app_dir(t_tok *lst_node, t_data *d_node, t_tok **lst, t_data **data)
{
	if (d_node)
	{
		if (d_node->outfile)
			free(d_node->outfile);
		d_node->outfile = ft_strdup(lst_node->next->token);
		if (!d_node->outfile)
			clean_parsing(lst, data);
		if (check_out_file(d_node->outfile, d_node, lst, data) == 0)
			return ;
		d_node->is_append = 1;
	}
	process_node_redir(lst_node, lst);
}

int	check_redir(t_tok **lst, t_tok **lst_node, t_data **data, t_data *node)
{
	if (ft_strcmp((*lst_node)->token, "<<"))
		return (at_heredoc(*lst_node, node, lst, data), 1);
	else if (ft_strcmp((*lst_node)->token, ">>"))
		return (app_dir(*lst_node, node, lst, data), 1);
	else if (ft_strcmp((*lst_node)->token, "<"))
		return (in_redir(*lst_node, node, lst, data), 1);
	else if (ft_strcmp((*lst_node)->token, ">"))
		return (out_redir(*lst_node, node, lst, data), 1);
	else
		return (0);
}
