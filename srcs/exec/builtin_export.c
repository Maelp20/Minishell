/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:37:16 by mpignet           #+#    #+#             */
/*   Updated: 2022/12/06 17:16:45 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_envp	*sort_envp(t_envp *envp)
{
	printf("sort_env\n");
	char	*buff1;
	char	*buff2;
	t_envp	*first_node;

	first_node = envp;
	while (envp->next)
	{
		if ((ft_strcmp(envp->var[0], envp->next->var[0]) > 0))
		{
			buff1 = envp->var[0];
			buff2 = envp->var[1];
			envp->var[0] = envp->next->var[0];
			envp->var[1] = envp->next->var[1];
			envp->next->var[0] = buff1;
			envp->next->var[1] = buff2;
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
	printf("show_export\n");
	t_envp	*tmp;

	tmp = envp;
	sort_envp(tmp);
	while (tmp->next)
	{
		printf("declare -x ");
		printf("%s", tmp->var[0]);
		printf("\"%s\"\n", tmp->var[1]);
		tmp = tmp->next;
	}	
}

void	ft_export(t_data *data)
{
	printf("export\n");
	int		i;
	t_envp	*new;
	
	i = 0;
	new = malloc (sizeof(t_envp));
	if (!new)
		exit(EXIT_FAILURE);
	if (!data->args[1])
	{
		ft_show_export(data->envp);
		exit(EXIT_SUCCESS);
	}
	while (data->args[++i])
	{
		new->var = ft_split(data->args[i], '=');
		new->var[0] = ft_strjoin_spec(new->var[0], "=");
		if (seek_var_in_env(data->envp, data->args[1]))
			data->envp->var[1] = ft_strjoin(NULL, data->args[1]);
		else
			ft_envpadd_front(&(data->envp), new);
	}
	ft_show_export(data->envp);
}