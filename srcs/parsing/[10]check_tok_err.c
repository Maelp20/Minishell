/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [10]check_tok_err.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 02:49:46 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/21 13:15:26 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	verif_redir(t_tok **tok_lst, t_data **data)
{
	t_tok	*temp;

	temp = *tok_lst;
	while (temp)
	{
		if (ft_strcmp(temp->token, "<") && (temp->next
				&& ft_strcmp(temp->next->token, ">")))
		{
			disp_error(tok_lst, data, "\\n");
			return ;
		}
		temp = temp->next;
	}
}

void	verif_pipe(t_tok **tok_lst, t_data **data)
{
	t_tok	*temp;

	temp = *tok_lst;
	if (ft_strcmp(temp->token, "|"))
	{
		disp_error(tok_lst, data, "|");
		return ;
	}
	while (temp)
	{
		if (ft_strcmp(temp->token, "|") && !temp->next)
		{
			disp_error(tok_lst, data, "|");
			return ;
		}
		if (ft_strcmp(temp->token, "|") && (temp->next
				&& ft_strcmp(temp->next->token, "|")))
		{
			disp_error(tok_lst, data, "|");
			return ;
		}
		temp = temp->next;
	}
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
