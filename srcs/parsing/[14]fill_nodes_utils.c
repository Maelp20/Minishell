/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [14]fill_nodes_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:27:03 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/29 15:06:38 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	process_node(t_tok **node, t_tok **lst)
{
	t_tok	*temp;

	temp = (*node)->next;
	tok_del_one(*node);
	//printf("Process_node: %s\n", (*node)->token);
	*node = temp;
	*lst = temp;
}

void	one_node(t_tok **lst)
{
	t_tok	*temp;

	temp = (*lst)->next;
	tok_del_one(*lst);
	*lst = temp;
	temp = (*lst)->next;
	tok_del_one(*lst);
	*lst = temp;
}

void	multi_node(t_tok **lst_node, t_tok **lst)
{
	t_tok	*temp;
	t_tok	*temp2;

	temp = (*lst_node);
	temp2 = (*lst_node)->next;
	if ((*lst_node)->prev == NULL)
	{
		(*lst_node)->next->next->prev = NULL;
		*lst = (*lst_node)->next->next;
	}
	else
	{
		(*lst_node)->prev->next = (*lst_node)->next->next;
		if (temp->prev->next)
			temp->prev->next->prev = temp->prev;
	}
	tok_del_one(temp);
	tok_del_one(temp2);
}
