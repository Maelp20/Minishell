/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:28:55 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/30 23:46:42 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_array(char** array)
{
	int i;

	i = 0;
	while(array[i])
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
		if(data->args)
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

t_data	*lstnew_args(char *content)
{
	t_data  *dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->args[0] = ft_strdup(content);
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

void	init_args(t_data **data, char *arg)
{

	int i;
	char **tmp;
	
	*data = NULL;
	i = 0;
	tmp = ft_split(arg, ' ');
	while (tmp[i])
	{
		lstadd_back_args(data ,lstnew_args(tmp[i]));
		i++;
	}
	free_array(tmp);
}
