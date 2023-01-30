/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [14]fill_nodes_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:27:03 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/30 18:01:11 by yanthoma         ###   ########.fr       */
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

// void	one_node(t_tok **lst)
// {
// 	t_tok	*temp;
// 	t_tok	*temp2;

// 	temp = (*lst)->next;
// 	temp2 = (*lst)->prev;
// 	tok_del_one(*lst);
// 	*lst = temp;
// 	if (temp2)
// 	{	
// 		//temp2->next = NULL;
// 		temp2->next = temp;
// 		}
// 	if (temp)
// 	{
// 			//temp->prev = NULL;
// 			temp->prev = temp2;
// 		}
// }

// void	multi_node(t_tok **lst_node, t_tok **lst)
// {
// 	t_tok	*temp;
// 	t_tok	*temp2;

// 	temp = (*lst_node);
// 	temp2 = (*lst_node)->next;
// 	if ((*lst_node)->prev == NULL)
// 	{
// 		(*lst_node)->next->next->prev = NULL;
// 		*lst = (*lst_node)->next->next;
// 	}
// 	else
// 	{
// 		(*lst_node)->prev->next = (*lst_node)->next->next;
// 		if (temp->prev->next)
// 			temp->prev->next->prev = temp->prev;
// 	}
// 	tok_del_one(temp);
// 	tok_del_one(temp2);
// }



/////

void	tok_delone(t_tok *node)
{
	free(node->token);
	free(node);
}

/*Clean all the t_tok linked list from the ptr*/

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

/*Add t_tok node to the back of t_tok linked list*/

void	tok_addback(t_tok **lst, t_tok *node)
{
	t_tok	*temp;

	if (!(*lst))
	{
		*lst = node;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

/*Create a new t_tok node, crash minishell if malloc failed*/

t_tok	*tok_new(char *str)
{
	t_tok	*result;

	if (!str)
		return (NULL);
	result = ft_calloc(1, sizeof(t_tok));
	if (!result)
		return (NULL);
	result->token = str;
	result->next = NULL;
	return (result);
}