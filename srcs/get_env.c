/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:17:27 by yanthoma          #+#    #+#             */
/*   Updated: 2022/11/08 14:38:52 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

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

void	lstadd_back_env(t_envp **lst, t_envp *new)
{
	t_env *last = ft_last(lst);
	
	if (*lst == ((void *)0))
		*lst = new;
	else
		lstadd_back_env(&((*lst)->next), new);
		//lstadd_back_env(&((*lst)->prev), last);
}

void	get_env(char **envi, t_data *data)
{
	int i;

	data->envp = NULL;
	i = -1;
	while (envi[++i])
		lstadd_back_env(&data->envp ,lstnew_env(ft_split(envi[i], '=')));
	// while(envp)
	// {
	// 	printf("%s\n %s\n", envp->var[0],envp->var[1] );
	// 	envp = envp->next;
	// }
}