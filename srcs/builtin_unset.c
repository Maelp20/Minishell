/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:10:01 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/14 18:32:43 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_unset(t_data *cmd)
{
	int		i;
	int		found;
	
	i = 0;
	found = 0;
	if (!envp)
		return (NULL);
	while (envp->var)
	{
		if (ft_strnstr(envp->var[0], cmd->args[1], ft_strlen(cmd->args[1])))
		{
			found = 1;
			break ;
		}
		envp = envp->next;
	}
	if (found)
	{		
		free(envp->var[0]);
		free(envp->var[1]);
	}
}