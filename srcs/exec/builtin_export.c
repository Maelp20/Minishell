/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:37:16 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/27 21:41:22 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	replace_var_in_env(t_envp *envp, t_envp *new)
{
	if (!new || !envp)
		return (0);
	while (envp)
	{
		if (ft_strnstr(envp->var[0], new->var[0], ft_strlen(new->var[0])))
			envp = new;
		envp = envp->next;
	}
	return (0);
}

int	check_valid_identifier(char *str)
{
	char	*invalid;
	int		i;
	int		j;

	invalid = "!@#$%^&*()`~-|[]{};:,./<>?";
	if (ft_strcmp(str, "="))
		return (msg_invalid_id(str, 0), g_var.g_status);
	if (str[0] >= '0' && str[0] <= '9')
		return (msg_invalid_id(str, 0), g_var.g_status);
	i = -1;
	while (str[++i] && str[i] != '=')
	{
		j = -1;
		while (invalid[++j])
		{
			if (invalid[j] == str[i])
				return (msg_invalid_id(str, 0), g_var.g_status);
			if (str[i] == '+' && str[i + 1] && str[i + 1] != '=')
				return (msg_invalid_id(str, 0), g_var.g_status);
		}
	}
	if (i == 0)
		return (msg_invalid_id(str, 0), g_var.g_status);
	return (0);
}

int	check_for_option_export(char *str)
{
	if (str[0] == '-')
		return (msg_invalid_option(str, 0), 1);
	return (0);
}

t_envp	*ft_prepare_new_var(char *arg)
{
	t_envp	*new;

	new = ft_calloc(1, sizeof(t_envp));
	if (!new)
		return (perror("malloc"), exit(set_err_status(1)), NULL);
	new->var = ft_split(arg, '=');
	if (!new->var)
		return (perror("malloc"), exit(set_err_status(1)), NULL);
	new->var[0] = ft_strjoin_spec(new->var[0], "=");
	if (!new->var[0])
		return (perror("malloc"), exit(set_err_status(1)), NULL);
	return (new);
}

int	ft_export(t_data *data)
{
	int		i;
	t_envp	*new;

	g_var.g_status = 0;
	i = 0;
	if (!data->args[1])
		return (ft_show_export(data->envp), g_var.g_status);
	if (check_for_option_export(data->args[1]))
		return (2);
	while (data->args[++i])
	{
		if (check_valid_identifier(data->args[i]))
			continue ;
		new = NULL;
		new = ft_prepare_new_var(data->args[i]);
		if (!replace_var_in_env(data->envp, new))
			ft_envpadd_back(&(data->envp), new);
	}
	return (g_var.g_status);
}
