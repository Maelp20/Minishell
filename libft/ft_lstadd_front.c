/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 21:33:22 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/13 21:33:22 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>
int        main(int ac, char **av)
{
	(void)ac;
	t_list    *elem;
	t_list		*add;

	add = ft_lstnew("pourquoi");
	elem = ft_lstnew((void *)av[1]);
	int i = 2;
	
	while (av[i])
	{
		ft_lstadd_front(&elem, ft_lstnew((void *)av[i]));
		i++;
	}

    ft_lstadd_front(&elem, add);
    while (elem != NULL)
	{
		printf("%s\n", (char *)elem->content);
		elem = elem->next;
	}
} */