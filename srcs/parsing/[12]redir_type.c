/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [12]redir_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:22:40 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/30 17:53:42 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// void	at_heredoc(t_tok **lst, t_tok **lst_node, t_data **data, t_data *node)
// {
// if (check_next_operator((*lst_node)->next, lst, data))
// 		return ;
// 	if (node->is_heredoc)
// 		free(node->is_heredoc);
// 	if (!(*lst_node)->next->next)
// 	{
// 		node->is_heredoc = ft_strdup((*lst_node)->next->token);
// 		ft_heredoc(*data);
// 		node->is_append = 1;
// 		if (!node->is_heredoc)
// 			clean_parsing(lst, data);
// 		process_node(lst_node, lst);
// 		process_node(lst_node, lst);
// 		return ;
// 	}	
// 	if (ft_strcmp((*lst_node)->token, (*lst)->token))
// 	{
// 		node->is_heredoc = ft_strdup((*lst_node)->next->token);
// 		ft_putstr_fd("test0\n", 2);
// 		ft_heredoc(*data);
// 		ft_putstr_fd("test\n", 2);
// 		node->is_append = 1;
// 		if (!node->is_heredoc)
// 			clean_parsing(lst, data);
// 		one_node(lst_node);
// 		one_node(lst_node);
// 		*lst = *lst_node;
// 		return ;
// 	}	
// 	if (!(*lst_node)->next)
// 		clean_parsing(lst, data);
// 	node->is_heredoc = ft_strdup((*lst_node)->next->token);
// 	ft_heredoc(*data);
// 	ft_putstr_fd("test2\n", 2);
// 	if (!node->is_heredoc)
// 		clean_parsing(lst, data);
// 	multi_node(lst_node, lst);
// }

// void	app_dir(t_tok **lst, t_tok **lst_node, t_data **data, t_data *node)
// {
// 	if (check_next_operator((*lst_node)->next, lst, data))
// 		return ;
// 	if (node->outfile)
// 		free(node->outfile);
// 	if (ft_strcmp((*lst_node)->token, (*lst)->token))
// 	{
// 		node->outfile = ft_strdup((*lst_node)->next->token);
// 		node->is_append = 1;
// 		if (!node->outfile)
// 			clean_parsing(lst, data);
// 		if(check_out_file(node->outfile,node, lst, data) == 0)
// 			return ;
// 		one_node(lst_node);
// 		one_node(lst_node);
// 		*lst = *lst_node;
// 		return ;
// 	}
// 	if (!(*lst_node)->next->next)
// 	{
// 		node->outfile = ft_strdup((*lst_node)->next->token);
// 		node->is_append = 1;
// 		if (!node->outfile)
// 			clean_parsing(lst, data);
// 		if(check_out_file(node->outfile,node, lst, data) == 0)
// 			return ;
// 		one_node(lst_node);
// 		one_node(lst_node);
// 		return ;
// 	}	
// 	if (!(*lst_node)->next)
// 		clean_parsing(lst, data);
// 	node->outfile = ft_strdup((*lst_node)->next->token);
// 	if (!node->outfile)
// 		clean_parsing(lst, data);
// 	if(check_out_file(node->outfile,node, lst, data) == 0)
// 		return ;
// 	node->is_append = 1;
// 	multi_node(lst_node, lst);
// }

// void	out_redir(t_tok **lst, t_tok **lst_node, t_data **data, t_data *node)
// {
// 	if (check_next_operator((*lst_node)->next, lst, data))
// 		return ;
// 	if (node->outfile)
// 		free(node->outfile);
// 	if (ft_strcmp((*lst_node)->token, (*lst)->token))
// 	{
// 		node->outfile = ft_strdup((*lst_node)->next->token);
// 		node->is_append = 0;
// 		if (!node->outfile)
// 			clean_parsing(lst, data);
// 		if (check_out_file(node->outfile,node, lst, data) == 0)
// 			return ;
// 		one_node(lst_node);
// 		one_node(lst_node);
// 		*lst = *lst_node;
// 		return ;
// 	}	
// 	if (!(*lst_node)->next->next)
// 	{
// 		node->outfile = ft_strdup((*lst_node)->next->token);
// 		node->is_append = 0;
// 		if (!node->outfile)
// 			clean_parsing(lst, data);
// 		if(check_out_file(node->outfile,node, lst, data) == 0)
// 			return ;
// 		one_node(lst_node);
// 		one_node(lst_node);
// 		return ;
// 	}	
// 	if (!(*lst_node)->next)
// 		clean_parsing(lst, data);
// 	node->outfile = ft_strdup((*lst_node)->next->token);
// 	if (!node->outfile)
// 		clean_parsing(lst, data);
// 	check_out_file(node->outfile,node, lst, data);
// 	node->is_append = 0;
// 	multi_node(lst_node, lst);
// }

// void	in_redir(t_tok **lst, t_tok **lst_node, t_data **data, t_data *node)
// {
// 	if (check_next_operator((*lst_node)->next, lst, data))
// 		return ;
// 	if (node->infile)
// 		free(node->infile);
// 	if (ft_strcmp((*lst_node)->token, (*lst)->token))
// 	{
// 		node->infile = ft_strdup((*lst_node)->next->token);
// 		if (!node->infile)
// 			clean_parsing(lst, data);
// 		check_in_file(node->infile,node, lst, data);
// 		one_node(lst_node);
// 		one_node(lst_node);
// 		*lst = *lst_node;
// 		return ;
// 	}	
// 	if ( !(*lst_node)->next->next)
// 	{
// 		node->infile = ft_strdup((*lst_node)->next->token);
// 		if (!node->infile)
// 			clean_parsing(lst, data);
// 		if (check_in_file(node->infile,node, lst, data) == 0)
// 			return ;
// 		one_node(lst_node);
// 		one_node(lst_node);
// 		return ;
// 	}
// 	if (!(*lst_node)->next)
// 		clean_parsing(lst, data);
// 	node->infile = ft_strdup((*lst_node)->next->token);
// 	if (!node->infile)
// 		clean_parsing(lst, data);
// 	if (check_in_file(node->infile,node, lst, data) == 0)
// 		return ;
// 	multi_node(lst_node, lst);
// }



void	delete_token_redir(t_tok *node, t_tok **lst)
{
	t_tok	*temp;
	t_tok	*temp2;

	if (ft_strcmp(node->token, (*lst)->token))
	{
		temp = (*lst)->next;
		tok_delone(*lst);
		*lst = temp;
		temp = (*lst)->next;
		tok_delone(*lst);
		*lst = temp;
		return ;
	}
	temp = *lst;
	while (!ft_strcmp(temp->next->token, node->token))
		temp = temp->next;
	temp2 = temp->next->next;
	tok_delone(temp->next);
	temp->next = temp2;
	if (temp->next->next)
		temp2 = temp->next->next;
	else
		temp2 = NULL;
	tok_delone(temp->next);
	temp->next = temp2;
}



void	at_heredoc(t_tok *r_token, t_data *c_node, t_tok **lst, t_data **mini)
{
	if (check_next_operator(r_token->next, lst, mini) == 1)
		return ;
	if (c_node)
	{
		if (c_node->is_heredoc)
			free(c_node->is_heredoc);
		c_node->is_heredoc = ft_strdup(r_token->next->token);
		ft_heredoc(c_node);
		// if (!c_node->infile)
		// 	ut_clean_parsing_n_quit(mini, lst, errno);
		
	}
	delete_token_redir(r_token, lst);
}

void	in_redir(t_tok *r_token, t_data *c_node, t_tok **lst, t_data **mini)
{
	if (check_next_operator(r_token->next, lst, mini) == 1)
		return ;
	if (c_node)
	{
		if (c_node->infile)
			free(c_node->infile);
		c_node->infile = ft_strdup(r_token->next->token);
		// if (!c_node->infile)
		// 	ut_clean_parsing_n_quit(mini, lst, errno);
		check_in_file(c_node->infile, c_node, lst, mini);
	}
	delete_token_redir(r_token, lst);
}

void	out_redir(t_tok *r_token, t_data *c_node, t_tok **lst, t_data **mini)
{
	if (check_next_operator(r_token->next, lst, mini) == 1)
		return ;
	if (c_node)
	{
		if (c_node->outfile)
			free(c_node->outfile);
		c_node->outfile = ft_strdup(r_token->next->token);
		// if (!c_node->outfile)
		// 	ut_clean_parsing_n_quit(mini, lst, errno);
		check_out_file(c_node->outfile, c_node, lst, mini);
	}
	delete_token_redir(r_token, lst);
}

void	app_dir(t_tok *r_token, t_data *c_node, t_tok **lst, t_data **mini)
{
	if (check_next_operator(r_token->next, lst, mini) == 1)
		return ;
	if (c_node)
	{
		if (c_node->outfile)
			free(c_node->outfile);
		c_node->outfile = ft_strdup(r_token->next->token);
		// if (!c_node->outfile)
		// 	ut_clean_parsing_n_quit(mini, lst, errno);
		check_out_file(c_node->outfile, c_node, lst, mini);
		c_node->is_append = 1;
	}
	delete_token_redir(r_token, lst);
}

int	check_redir(t_tok **lst, t_tok **lst_node, t_data **data, t_data *node)
{
	if (ft_strcmp((*lst_node)->token, "<<"))
		return (at_heredoc(*lst_node, node,lst, data), 1);
	else if (ft_strcmp((*lst_node)->token, ">>"))
		return (app_dir(*lst_node, node,lst, data), 1);
	else if (ft_strcmp((*lst_node)->token, "<"))
		return (in_redir(*lst_node, node,lst, data), 1);
	else if (ft_strcmp((*lst_node)->token, ">"))
		return (out_redir(*lst_node, node,lst, data), 1);
	else
		return (0);
}
