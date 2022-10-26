/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:03:07 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/15 20:03:07 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(int))
{
	if (lst && f)
	{
		while (lst->next != NULL)
		{
			(*f)(lst->content);
			lst = lst->next;
		}
		(*f)(lst->content);
	}	
}
/*
#include <stdio.h>

static void ft_print(void *elem)
{
    printf("%s\n", (char *)elem);
}

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
	ft_lstiter(elem, ft_print);
}*/