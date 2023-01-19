/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:47:57 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/19 18:52:19 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	disp_error(t_tok **tok_lst, t_data **data, char *token)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	ft_free_data(*data);
	ft_free_tok(tok_lst);
	err_status = 2;
}

void clean_parsing(t_tok **lst, t_data **data)
{
	perror("malloc :");
	ft_free_tok(lst);
	ft_free_data(data);
}

void	ft_free_tok(t_tok **lst_tok)
{
	t_tok *tmp;

	while(*lst_tok)
	{
		tmp = *lst_tok;
		*lst_tok = (*lst_tok)->next;
		if (tmp->token)
			free(tmp->token);
		free (tmp);
	}
}

void 