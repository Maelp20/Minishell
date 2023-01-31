/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [14]fill_nodes_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:27:03 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/31 02:18:25 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	process_node(t_tok **node, t_tok **lst)
{
	t_tok	*temp;

	temp = (*node)->next;
	tok_delone(*node);
	*node = temp;
	*lst = temp;
}

void	tok_delone(t_tok *node)
{
	free(node->token);
	free(node);
}

void	clean_tok(t_tok **lst)
{
	t_tok	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->token)
			free((*lst)->token);
		free((*lst));
		*lst = temp;
	}
}
