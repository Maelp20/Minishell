/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tok_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 02:49:46 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/19 15:20:39 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	destroy_struct(t_tok **tok_lst, t_data **data, char *token)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	ft_free_data(*data);
	ft_free_tok(tok_lst);
	err_status = 2;
}

void	verif_redir(t_tok **tok_lst, t_data **data)
{
	t_tok	*temp;

	temp = *tok_lst;
	while (temp)
	{
		if (ft_strcmp(temp->token, "<") && (temp->next
				&& ft_strcmp(temp->next->token, ">")))
		{
			destroy_struct(tok_lst, data, "\\n");
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
		destroy_struct(tok_lst, data, "|");
		return ;
	}
	while (temp)
	{
		if (ft_strcmp(temp->token, "|") && !temp->next)
		{
			destroy_struct(tok_lst, data, "|");
			return ;
		}
		if (ft_strcmp(temp->token, "|") && (temp->next
				&& ft_strcmp(temp->next->token, "|")))
		{
			destroy_struct(tok_lst, data, "|");
			return ;
		}
		temp = temp->next;
	}
}