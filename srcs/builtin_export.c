/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:37:16 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/14 14:29:28 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

t_envp	*sort_envp(t_envp *envp)
{
	char	*buff;
	t_envp	*first_node;

	first_node = envp;
	while (envp->next->next)
	{
		if ((ft_strcmp(envp->var[0], envp->next->var[0])))
		{
			buff = envp->var[0];
			envp->var[0] = envp->next->var[0];
			envp->next->var[0] = buff;
			envp = first_node;
		}
		else
			envp = envp->next;
	}
	envp = first_node;
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
	t_envp	*new;
	
	new = malloc (sizeof(t_envp));
	if (!new)
		return ;
	if (!cmd->args[1])
		ft_show_export(envp);
	else
	{
		new->var = ft_split(cmd->args, '=');
		new->var[0] = ft_strjoin_spec(new->var[0], "=");
		ft_envpadd_front(&envp, new);
	}
}