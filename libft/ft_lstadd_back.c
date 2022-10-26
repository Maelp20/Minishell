/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:11:37 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/14 13:11:37 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == ((void *)0))
		*lst = new;
	else
		ft_lstadd_back(&((*lst)->next), new);
}

/*
#include <stdio.h>
int main (int ac, char **av)
{
	(void)ac;
	t_list *elem;
	int i = 2;
	elem = ft_lstnew((void *)av[1]);
	while (av[i])
	{
		ft_lstadd_back(&elem, ft_lstnew((void *)av[i]));
		i++;
	}
	while (elem)
	{
		printf("%s\n", (char *)elem->content);
		elem = elem->next;
	}
}*/
