/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 23:59:00 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/13 23:59:00 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	return (ft_lstlast(lst->next));
}
/*
#include <stdio.h>
int        main(int ac, char **av)
{
	(void)ac;
	t_list	*elem;
	t_list	*last;

	elem = ft_lstnew((void *)av[1]);
	int i = 2;
	
	while (av[i])
	{
		ft_lstadd_front(&elem, ft_lstnew((void *)av[i]));
		i++;
	}
	last = ft_lstlast(elem);
		printf("%s\n", (char *)last->content);
}*/	
