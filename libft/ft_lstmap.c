/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 21:18:55 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/15 21:18:55 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, int (*f)(int), void (*del)(int))
{
	t_list	*cpy;
	t_list	*new;

	new = NULL;
	if (!f || !lst || !del)
		return (NULL);
	while (lst)
	{
		cpy = ft_lstnew(f(lst->content));
		if (!cpy)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, cpy);
		lst = lst->next;
	}
	return (new);
}
/*

#include <stdio.h>
#include <string.h>

void *ft_cpy(void *elem)
{
	t_list	*test;
	(void)elem;

	test = ft_lstnew("non");
	return (test);
}

void ft_print(void *elem)
{
    printf("%s\n", (char *)elem);
}

int main (int ac, char **av)
{
	(void)ac;
	t_list  *base_list;
    t_list  *new_list;

	int i = 2;
	base_list = ft_lstnew((void *)av[1]);
    while (av[i])
	{
		ft_lstadd_back(&base_list, ft_lstnew((void *)av[i]));
		i++;
	}
  	new_list = ft_lstmap(base_list, ft_cpy,free);
	ft_lstiter(base_list, ft_print);
	ft_lstiter(new_list, ft_print);
}*/