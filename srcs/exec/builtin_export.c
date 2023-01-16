/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:37:16 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/16 15:30:32 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* We sort env in ASCII order. */

int	replace_var_in_env(t_envp *envp, t_envp *new)
{
	if (!new || !envp)
		return (1);
	while (envp)
	{
		if(ft_strnstr(envp->var[0], new->var[0], ft_strlen(new->var[0])))
		{
			envp->var[1] = ft_strdup(new->var[1]);
			return (1);
		}
		envp = envp->next;
	}
	return (0);
}

void	sort_envp(t_envp *envp)
{
	char	*buff1;
	char	*buff2;
	t_envp	*first_node;

	first_node = envp;
	while (envp->next)
	{
		if ((ft_strcmp_spec(envp->var[0], envp->next->var[0]) > 0))
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
}

/* We copy env in dst without the last line ("_=...") because we don't want it in export */

t_envp *copy_envp(t_envp *envp)
{
	t_envp *dst = NULL;
	t_envp *tmp;

	while (envp)
	{
		if (!ft_strcmp(envp->var[0], "_="))
		{			
			tmp = malloc(sizeof(t_envp));
			tmp->var = malloc(sizeof(char *) * 3);
			tmp->var[0] = ft_strdup(envp->var[0]);
			if (envp->var[1])
				tmp->var[1]= ft_strdup(envp->var[1]);
			tmp->var[2] = NULL;
			tmp->next = dst;
			dst = tmp;
		}
		envp = envp->next;
	}
	return (dst);
}

/* Show export : sorting env in ASCII order and adding "declare -x" each line. */

void	ft_show_export(t_envp *envp)
{
	t_envp	*dst;

	dst = copy_envp(envp);
	sort_envp(dst);
	while (dst)
	{
		printf("export ");
		if (!dst->var[1])
		{
			dst->var[0] = ft_strtrim(dst->var[0], "=");
			printf("%s", dst->var[0]);
		}
		else
		{
			printf("%s", dst->var[0]);
			printf("\"%s\"", dst->var[1]);
		}
		printf("\n");
		dst = dst->next;
	}
	free(dst);
}

/* Export builtin : 
- Without args : we show export.
- With args : we add the named variable to env, or if it already exists, we replace it's value
with our newly defined value. */

void	ft_export(t_data *data)
{
	int		i;
	t_envp	*new;
	
	i = 0;
	if (!data->args[1])
	{
		ft_show_export(data->envp);
		return;
		exit(EXIT_SUCCESS);
	}
	while (data->args[++i])
	{
		new = malloc (sizeof(t_envp));
		if (!new)
			exit(EXIT_FAILURE);
		new->var = ft_split(data->args[i], '=');
		new->var[0] = ft_strjoin_spec(new->var[0], "=");
		if (!replace_var_in_env(data->envp, new))
			ft_envpadd_back(&(data->envp), new);
	}
	//ft_show_export(data->envp);
}