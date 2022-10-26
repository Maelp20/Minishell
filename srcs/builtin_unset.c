/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:10:01 by mpignet           #+#    #+#             */
/*   Updated: 2022/10/26 16:32:25 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

int	ft_unset(t_cmd *cmd, t_envp *envp)
{
	int		i;
	
	i = 0;
	if (!envp)
		return (NULL);
	while (envp->var)
	{
		if (ft_strnstr(envp->var[0], cmd->args[1], ft_strlen(cmd->args[1])))
			break ;
		envp = envp->next;
	}
	free(envp->var[0]);
	free(envp->var[1]);
}