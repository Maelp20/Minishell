/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:56:48 by yanthoma          #+#    #+#             */
/*   Updated: 2022/04/13 15:56:48 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char **content)
{
	t_list	*dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->content = content;
	dest->next = NULL;
	return (dest);
}

/*#include <stdio.h>
int        main(void)
{
    char *str = "fais chier";
	t_list    *elem;
    elem = ft_lstnew(str);
    printf("%s\n", (char *)elem->content);
}*/