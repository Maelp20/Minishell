/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:37:16 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/11 17:01:40 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

t_envp	*sort_envp(t_envp *envp)
{
	char	*buff;
	t_envp	*begin;
	t_envp	*last;
	int		i;

	begin = envp;
	last = ft_envplast(envp);
	i = 0;
	while (envp->next->next)
	{
		if (envp->var[0][0] < 'A' || envp->var[0][0] > 'Z')
		{
			
		}
	}
	while (envp->next->next)
	{
		if ((ft_strcmp(envp->var[0], envp->next->var[0])))
		{
			buff = envp->var[0];
			envp->var[0] = envp->next->var[0];
			envp->next->var[0] = buff;
			envp = begin;
		}
		else
			envp = envp->next;
	}
	envp = begin;
	return (envp);
}

void	ft_show_export(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	sort_envp(tmp);
	while (tmp)
	{
		printf("declare -x ");
		printf("%s", tmp->var[0]);
		printf("\"%s\"\n", tmp->var[1]);
		tmp = tmp->next;
	}	
}

void	ft_export(t_cmd *cmd, t_envp *envp)
{
	if (!cmd->args[1])
		ft_show_export(envp);
	else
}