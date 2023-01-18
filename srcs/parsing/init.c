/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:28:55 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/18 03:30:40 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	destroy_struct(t_data *data)
{
	while (data)
	{
		if (data->args)
			free_array(data->args);
		if (data->cmd_path)
			free(data->cmd_path);
		while (data->envp)
		{
			if (data->envp->var)
				free_array(data->envp->var);
			data->envp = data->envp->next;
		}
		free(data->envp);
		data = data->next;
	}
	free(data);
}

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
