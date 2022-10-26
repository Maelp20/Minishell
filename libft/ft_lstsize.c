/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 23:37:42 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/13 23:37:42 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
#include <stdio.h>
int main (int ac, char **av)
{
	(void)ac;
	t_list *elem;
	int i;

	i = 2;
	elem = ft_lstnew((void *)av[1]);
	while (av[i])
	{
		ft_lstadd_front(&elem, ft_lstnew((void *)av[i]));
		i++;
	}

	printf("%d\n", ft_lstsize(elem));
	while (elem != NULL)
	{
		printf("%s\n", (char *)elem->content);
		elem = elem->next;
	}
}*/