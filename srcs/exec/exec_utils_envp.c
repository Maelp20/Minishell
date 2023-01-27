/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_envp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:33:59 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/27 20:17:41 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_envp	*ft_envpnew(char *var, char *value)
{
	t_envp	*new;

	new = (t_envp *)ft_calloc(sizeof(t_envp), 1);
	if (!new)
		return (perror("malloc"), exit(set_err_status(1)), NULL);
	new->var = (char **)ft_calloc(sizeof(char *), 3);
	if (!new->var)
		return (perror("malloc"), free(new), exit(set_err_status(1)), NULL);
	new->var[0] = ft_strdup(var);
	if (!new->var[0])
		return (perror("malloc"), free(new), free(new->var),
			exit(set_err_status(1)), NULL);
	new->var[1] = value;
	new->var[2] = NULL;
	new->next = NULL;
	return (new);
}

t_envp	*ft_envplast(t_envp *envp)
{
	if (!envp)
		return (0);
	while (envp->next)
		envp = envp->next;
	return (envp);
}

void	ft_envpadd_front(t_envp **envp, t_envp *new)
{
	if (!envp || !new)
		return ;
	new->next = *envp;
	*envp = new;
}

void	ft_envpadd_back(t_envp **envp, t_envp *new)
{
	t_envp	*tmp;

	if (!envp)
		return ;
	if (!*envp)
		*envp = new;
	else
	{
		tmp = ft_envplast(*envp);
		tmp->next = new;
	}
}

char	*seek_pwd_in_env(t_envp *envp)
{
	char	*buff;

	buff = NULL;
	if (!envp)
		return (NULL);
	while (envp)
	{
		if (ft_strcmp(envp->var[0], "PWD="))
		{
			buff = ft_strdup(envp->var[1]);
			if (!buff)
				return (perror("malloc"), exit(set_err_status(1)), NULL);
			break ;
		}
		envp = envp->next;
	}
	return (buff);
}
