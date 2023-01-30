/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:37:16 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/30 13:19:36 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	replace_var(t_envp *envp, t_envp *new, t_data *data)
{
	char	*tmp;

	tmp = ft_strdup(envp->var[1]);
	ft_free_dble_array((void **)envp->var);
	envp->var = ft_calloc(sizeof(char **), 3);
	if (!envp->var)
		return (perror("malloc"), clean_exit(data,
				set_err_status(1)), 1);
	envp->var[0] = ft_strdup(new->var[0]);
	if (new->var[1])
		envp->var[1] = ft_strdup(new->var[1]);
	else
		envp->var[1] = ft_strdup(tmp);
	envp->var[2] = NULL;
	ft_free_dble_array((void **)new->var);
	free(new);
	free(tmp);
	return (0);
}

int	replace_var_in_env(t_envp *envp, t_envp *new, t_data *data)
{
	int		plus;

	plus = ft_check_plus(new->var[0]);
	if (plus)
	{
		new->var[0] = ft_strtrim_spec(new->var[0], "+=");
		new->var[0] = ft_strjoin_spec(new->var[0], "=");
	}
	if (!new || !envp)
		return (0);
	while (envp)
	{
		if (ft_strnstr(envp->var[0], new->var[0], ft_strlen(new->var[0])))
		{
			if (plus)
				increment_var(envp, new, data);
			else
				replace_var(envp, new, data);
			return (1);
		}
		envp = envp->next;
	}
	return (0);
}

void	ft_fill_new_var(t_data *data, char **var, int count)
{
	var[0] = ft_strjoin_spec(var[0], "=");
	if (!var[0])
	{
		perror("malloc");
		clean_exit(data, set_err_status(1));
	}
	while (--count > 0)
		var[1] = ft_strjoin_free_s2("=", var[1]);
}

t_envp	*ft_prepare_new_var(char *arg, t_data *data)
{
	t_envp	*new;
	int		count;

	count = count_equal_signs(arg);
	new = ft_calloc(1, sizeof(t_envp));
	if (!new)
		return (perror("malloc"), clean_exit(data, set_err_status(1)), NULL);
	if (count)
	{
		new->var = ft_split(arg, '=');
		if (!new->var)
			return (perror("malloc"), clean_exit(data, set_err_status(1)),
				NULL);
	}
	else
	{
		new->var = ft_calloc(sizeof(char *), 2);
		if (!new->var)
			return (perror("malloc"), clean_exit(data, set_err_status(1)),
				NULL);
		new->var[0] = ft_strdup(arg);
		new->var[1] = NULL;
		count++;
	}
	return (ft_fill_new_var(data, new->var, count), new);
}

int	ft_export(t_data *data)
{
	int		i;
	t_envp	*new;

	g_var.g_status = 0;
	i = 0;
	if (!data->args[1])
		return (ft_show_export(data->envp, data), g_var.g_status);
	if (check_for_option_export(data->args[1]))
		return (2);
	while (data->args[++i])
	{
		if (check_valid_identifier(data->args[i]))
			continue ;
		new = ft_prepare_new_var(data->args[i], data);
		if (!replace_var_in_env(data->envp, new, data))
			ft_envpadd_back(&(data->envp), new);
	}
	return (g_var.g_status);
}
