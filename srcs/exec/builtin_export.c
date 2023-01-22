/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:37:16 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/22 20:05:03 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* We sort env in ASCII order. */

int	replace_var_in_env(t_envp *envp, t_envp *new)
{
	if (!new || !envp)
		return (0);
	while (envp)
	{
		if (ft_strnstr(envp->var[0], new->var[0], ft_strlen(new->var[0])))
		{
			free(envp->var[1]);
			envp->var[1] = ft_strdup(new->var[1]);
			{
				ft_free_dble_array((void **)new->var);
				free(new);
				return (1);
			}
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

/* We copy env in dst without the last line ("_=...") 
because we don't want it in export */

t_envp	*copy_envp(t_envp *envp)
{
	t_envp	*dst;
	t_envp	*tmp;

	dst = NULL;
	while (envp)
	{
		if (!ft_strcmp(envp->var[0], "_="))
		{			
			tmp = malloc(sizeof(t_envp));
			tmp->var = malloc(sizeof(char *) * 3);
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

/* Show export : sorting env in ASCII order and adding "declare -x" 
each line. */

void	ft_show_export(t_envp *envp)
{
	t_envp	*first_node;
	t_envp	*dst;

	dst = copy_envp(envp);
	sort_envp(dst);
	first_node = dst;
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
	ft_envpclear(&first_node);
}

/* Export builtin : 
- Without args : we show export.
- With args : we add the named variable to env, or if it already exists,
 we replace it's value
with our newly defined value. */

int	check_valid_identifier(char *str)
{
	char	*invalid;
	int		i;
	int		j;

	invalid = "!@#$%^&*()`~-|[]{};:,./<>?";
	if (ft_strcmp(str, "="))
		return (msg_export_err(str), g_status);
	if (str[0] >= '0' && str[0] <= '9')
		return (msg_export_err(str), g_status);
	i = -1;
	while (str[++i] && str[i] != '=')
	{
		j = -1;
		while (invalid[++j])
		{
			if (invalid[j] == str[i])
				return (msg_export_err(str), g_status);
			if (str[i] == '+' && str[i + 1] && str[i + 1] != '=')
				return (msg_export_err(str), g_status);
		}
	}
	if (i == 0)
		return (msg_export_err(str), g_status);
	return (0);
}

int	check_for_option_export(char *str)
{
	if (str[0] == '-')
		return (msg_export_option(str), set_err_status(2));
	return (0);
}

int	ft_export(t_data *data)
{
	int		i;
	t_envp	*new;

	g_status = 0;
	i = 0;
	if (!data->args[1])
		return (ft_show_export(data->envp), g_status);
	if (check_for_option_export(data->args[1]))
		return (2);
	while (data->args[++i])
	{
		if (check_valid_identifier(data->args[i]))
			continue ;
		new = ft_calloc(1, sizeof(t_envp));
		if (!new)
			return (perror("malloc"), set_err_status(1));
		new->var = ft_split(data->args[i], '=');
		new->var[0] = ft_strjoin_spec(new->var[0], "=");
		if (!replace_var_in_env(data->envp, new))
			ft_envpadd_back(&(data->envp), new);
	}
	return (g_status);
}
