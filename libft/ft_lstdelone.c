/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Untitled-1                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:19:22 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/15 17:19:22 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(int))
{
	if (!del)
		return ;
	if (lst)
	{
		(*del)(lst->content);
		free(lst);
	}
}
/*
#include <stdio.h>
static void ft_del(void *mem, size_t mem_size)
{
    if (mem)
    {
        free(mem);
        mem = NULL;
    }
    (void)mem_size;
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
	 ft_lstdelone(&elem, ft_del);
}*/