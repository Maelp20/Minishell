/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:17:27 by yanthoma          #+#    #+#             */
/*   Updated: 2022/12/05 21:14:25 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_envp	*lstnew_env(char **content)
{
	t_envp  *dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->var = content;
	dest->var[0]= ft_strjoin(dest->var[0], "=");
	dest->next = NULL;
	return (dest);
}

// void	lstadd_back_env(t_envp **lst, t_envp *new)
// {
// 	if (*lst == ((void *)0))
// 		*lst = new;
// 	else
// 		lstadd_back_env(&((*lst)->next), new);
// }

// void	get_env(char **envi, t_data *data)
// {
// 	int i;

// 	data->envp = NULL;
// 	i = -1;
// 	while (envi[++i])
// 		lstadd_back_env(&data->envp ,lstnew_env(ft_split(envi[i], '=')));
// }


void get_env(char **envi, t_data *data)
{
    int i;
    t_envp *node;
    t_envp **tail;

    data->envp = NULL;
    tail = &data->envp;

    for (i = 0; envi[i]; i++)
    {
        node = lstnew_env(ft_split(envi[i], '='));
        if (!node)
            continue;

        *tail = node;
        tail = &node->next;
    }
}
