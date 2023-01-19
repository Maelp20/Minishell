/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:28:55 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/19 18:49:33 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_data	*ft_lstlast_arg(t_data *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	return (ft_lstlast_arg(lst->next));
}

t_data	*lstnew_args(t_envp *envir)
{
	t_data	*dest;

	dest = ft_calloc(sizeof(t_data), 1);
	dest->envp = envir;
	dest->env = parse_env(dest->envp);
	if (!dest)
		return (NULL);
	dest->next = NULL;
	return (dest);
}

void	lstadd_back_args(t_data **lst, t_data *new)
{
	if (!(*lst))
		*lst = new;
	else
		lstadd_back_args(&((*lst)->next), new);
}
