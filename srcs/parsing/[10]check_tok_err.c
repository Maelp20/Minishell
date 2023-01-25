/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [10]check_tok_err.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 02:49:46 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/25 16:31:56 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"



static	int	comp_redir( t_tok *lst_node)
{
	if (ft_strcmp(lst_node->token, "<<"))
		return (1);
	else if (ft_strcmp(lst_node->token, ">>"))
		return ( 1);
	else if ( ft_strcmp(lst_node->token,"<"))
		return ( 1);
	else if (ft_strcmp(lst_node->token, ">"))
		return  (1);
	else
		return (0);
}

int	verif_redir(t_tok **tok_lst, t_data **data)
{
	t_tok	*temp;

	temp = *tok_lst;
	while (temp)
	{
		if (ft_strcmp(temp->token, "<") && (temp->next
				&& ft_strcmp(temp->next->token, ">")))
		{
			disp_error(tok_lst, data, "\\n");
			return (1);
		}
		if (comp_redir(temp) && !temp->next)
		{
			disp_error(tok_lst, data, "\\n");
			return (1);
		}
		if (comp_redir(temp) && ft_strcmp(temp->next->token, "|"))
		{
			disp_error(tok_lst, data, "|kk");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	verif_pipe(t_tok **tok_lst, t_data **data)
{
	t_tok	*temp;

	temp = *tok_lst;
	if (ft_strcmp(temp->token, "|"))
	{
		disp_error(tok_lst, data, "|");
		return (1);
	}
	while (temp)
	{
		if (ft_strcmp(temp->token, "|") && !temp->next)
		{
			disp_error(tok_lst, data, "|");
			return (1);
		}
		if (ft_strcmp(temp->token, "|") && (temp->next
				&& ft_strcmp(temp->next->token, "|")))
		{
			disp_error(tok_lst, data, "|");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	check_next_operator(t_tok *node, t_tok **tok_lst, t_data **data)
{
	if (!node)
		return (disp_error(tok_lst, data, "\\n"), 1);
	if (!node->token)
		return (1);
	if (node->token[0] == '|')
		return (disp_error(tok_lst, data, "|"), 1);
	if (node->token[0] == '<' && node->token[1] != '<')
		return (disp_error(tok_lst, data, "<"), 1);
	if (node->token[0] == '<' && node->token[1] == '<')
		return (disp_error(tok_lst, data, "<<"), 1);
	if (node->token[0] == '>' && node->token[1] != '>')
		return (disp_error(tok_lst, data, ">"), 1);
	if (node->token[0] == '>' && node->token[1] == '>')
		return (disp_error(tok_lst, data, ">>"), 1);
	return (0);
}
