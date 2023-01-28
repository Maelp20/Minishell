/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [14]fill_nodes_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:27:03 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/28 19:58:25 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	process_node(t_tok **node, t_tok **lst)
{
	t_tok	*temp;

	temp = (*node)->next;
	tok_del_one(*node);
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
