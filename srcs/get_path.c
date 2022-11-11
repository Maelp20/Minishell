/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:18:12 by yanthoma          #+#    #+#             */
/*   Updated: 2022/11/11 16:41:47 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

char	*get_path(t_data *data)
{
	int		i;
	t_envp	*tmp;

	i = 0 ;
	tmp = data->envp;
	while (ft_strncmp(data->envp->var[0], "PATH=", 5) != 0)
		data->envp = data->envp->next;
	data->path = ft_split(data->envp->var[1], ':');
	if (!data->path)
		return (NULL);
	while (data->path[i])
	{
		data->path[i] = ft_strjoin(data->path[i], "/");
		if (!data->path[i])
			return (NULL);
		i++;
	}
	data->envp = tmp;
	return (NULL);
}