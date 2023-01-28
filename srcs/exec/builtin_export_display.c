/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_display.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:12:28 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/28 17:51:09 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	sort_envp(t_envp *envp)
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

static t_envp	*copy_envp(t_envp *envp)
{
	t_envp	*dst;
	t_envp	*tmp;

	dst = NULL;
	while (envp)
	{
		if (!ft_strcmp(envp->var[0], "_="))
		{			
			tmp = ft_calloc(sizeof(t_envp), 1);
			if (!tmp)
				return (perror("malloc"), exit(set_err_status(1)), NULL);
			tmp->var = ft_calloc(sizeof(char *), 3);
			if (!tmp->var)
				return (perror("malloc"), free(tmp), exit(set_err_status(1)),
					NULL);
			tmp->var[0] = ft_strdup(envp->var[0]);
			if (envp->var[1])
				tmp->var[1] = ft_strdup(envp->var[1]);
			tmp->var[2] = NULL;
			tmp->next = dst;
			dst = tmp;
		}
		envp = envp->next;
	}
	return (dst);
}

static void	ft_print_only_var_name(char *var_name, t_data *data)
{
	char	*name_only;

	name_only = ft_strtrim(var_name, "=");
	if (!name_only)
	{
		perror("malloc");
		clean_exit(data, set_err_status(1));
	}
	printf("%s", name_only);
	free(name_only);
}

void	ft_show_export(t_envp *envp, t_data *data)
{
	t_envp	*first_node;
	t_envp	*dst;

	(void)data;
	dst = copy_envp(envp);
	sort_envp(dst);
	first_node = dst;
	while (dst)
	{
		printf("export ");
		if (!dst->var[1])
			ft_print_only_var_name(dst->var[0], data);
		else
		{
			printf("%s", dst->var[0]);
			printf("\"%s\"", dst->var[1]);
		}
		printf("\n");
		dst = dst->next;
	}
	ft_envpclear(&first_node);
}
