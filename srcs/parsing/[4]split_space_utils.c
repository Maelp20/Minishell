/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [4]split_space_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:20:13 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/28 19:57:25 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	tok_del_one(t_tok *lst)
{
	lst->token = NULL;
	if (lst->token)
		free(lst->token);
	lst = NULL;
	if (lst)
		free(lst);
}

t_tok	*lstnew_token(char *content)
{
	t_tok	*dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->token = ft_strdup(content);
	dest->next = NULL;
	return (dest);
}

t_tok	*lstnew_token2(char *content)
{
	t_tok	*dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->token = ft_strdup(content);
	dest->next = NULL;
	free(content);
	return (dest);
}

void	lstadd_back_token(t_tok **lst, t_tok *new)
{
	if (!(*lst))
		*lst = new;
	else
		lstadd_back_token(&((*lst)->next), new);
}

