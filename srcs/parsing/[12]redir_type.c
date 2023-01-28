/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [12]redir_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:22:40 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/28 19:59:34 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	at_heredoc(t_tok **lst, t_tok **lst_node, t_data **data, t_data *node)
{
	if (check_next_operator((*lst_node)->next, lst, data))
		return ;
	if (node->is_heredoc)
		free(node->is_heredoc);
	if (ft_strcmp((*lst_node)->token, (*lst)->token) || !(*lst_node)->next->next)
	{
		node->is_heredoc = ft_strdup((*lst_node)->next->token);
		ft_heredoc(*data);
		node->is_append = 1;
		if (!node->is_heredoc)
			clean_parsing(lst, data);
		one_node(lst_node);
		return ;
	}	
	if (!(*lst_node)->next)
		clean_parsing(lst, data);
	node->is_heredoc = ft_strdup((*lst_node)->next->token);
	ft_heredoc(*data);
	if (!node->is_heredoc)
		clean_parsing(lst, data);
	//multi_node(lst_node, lst);
}

void	app_dir(t_tok **lst, t_tok **lst_node, t_data **data, t_data *node)
{
	if (check_next_operator((*lst_node)->next, lst, data))
		return ;
	if (node->outfile)
		free(node->outfile);
	if (ft_strcmp((*lst_node)->token, (*lst)->token)|| !(*lst_node)->next->next)
	{
		node->outfile = ft_strdup((*lst_node)->next->token);
		node->is_append = 1;
		if (!node->outfile)
			clean_parsing(lst, data);
		check_out_file(node->outfile,node, lst, data);
		one_node(lst_node);
		return ;
	}	
	if (!(*lst_node)->next)
		clean_parsing(lst, data);
	node->outfile = ft_strdup((*lst_node)->next->token);
	if (!node->outfile)
		clean_parsing(lst, data);
	check_out_file(node->outfile,node, lst, data);
	node->is_append = 1;
	//multi_node(lst_node, lst);
}

void	out_redir(t_tok **lst, t_tok **lst_node, t_data **data, t_data *node)
{
	if (check_next_operator((*lst_node)->next, lst, data))
		return ;
	if (node->outfile)
		free(node->outfile);
	if (ft_strcmp((*lst_node)->token, (*lst)->token)|| !(*lst_node)->next->next)
	{
		node->outfile = ft_strdup((*lst_node)->next->token);
		node->is_append = 0;
		if (!node->outfile)
			clean_parsing(lst, data);
		check_out_file(node->outfile,node, lst, data);
		one_node(lst_node);
		return ;
	}	
	if (!(*lst_node)->next)
		clean_parsing(lst, data);
	node->outfile = ft_strdup((*lst_node)->next->token);
	if (!node->outfile)
		clean_parsing(lst, data);
	check_out_file(node->outfile,node, lst, data);
	node->is_append = 0;
	//multi_node(lst_node, lst);
}

void	in_redir(t_tok **lst, t_tok **lst_node, t_data **data, t_data *node)
{
	if (check_next_operator((*lst_node)->next, lst, data))
		return ;
	if (node->infile)
		free(node->infile);
	if (ft_strcmp((*lst_node)->token, (*lst)->token)|| !(*lst_node)->next->next)
	{
		node->infile = ft_strdup((*lst_node)->next->token);
		if (!node->infile)
			clean_parsing(lst, data);
		check_in_file(node->infile,node, lst, data);
		one_node(lst_node);
		return ;
	}	
	if (!(*lst_node)->next)
		clean_parsing(lst, data);
	node->infile = ft_strdup((*lst_node)->next->token);
	if (!node->infile)
		clean_parsing(lst, data);
	check_in_file(node->infile,node, lst, data);
	//multi_node(lst_node, lst);
}

int	check_redir(t_tok **lst, t_tok **lst_node, t_data **data, t_data *node)
{
	if (ft_strcmp((*lst_node)->token, "<<"))
		return (at_heredoc(lst, lst_node, data, node), 1);
	else if (ft_strcmp((*lst_node)->token, ">>"))
		return (app_dir(lst, lst_node, data, node), 1);
	else if (ft_strcmp((*lst_node)->token, "<"))
		return (in_redir(lst, lst_node, data, node), 1);
	else if (ft_strcmp((*lst_node)->token, ">"))
		return (out_redir(lst, lst_node, data, node), 1);
	else
		return (0);
}
