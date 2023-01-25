/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:37:16 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/25 20:44:07 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* Export builtin : 
- Without args : we show export.
- With args : we add the named variable to env, or if it already exists,
 we replace it's value
with our newly defined value. */

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

int	check_valid_identifier(char *str)
{
	char	*invalid;
	int		i;
	int		j;

	invalid = "!@#$%^&*()`~-|[]{};:,./<>?";
	if (ft_strcmp(str, "="))
		return (msg_invalid_id(str, 0), g_status);
	if (str[0] >= '0' && str[0] <= '9')
		return (msg_invalid_id(str, 0), g_status);
	i = -1;
	while (str[++i] && str[i] != '=')
	{
		j = -1;
		while (invalid[++j])
		{
			if (invalid[j] == str[i])
				return (msg_invalid_id(str, 0), g_status);
			if (str[i] == '+' && str[i + 1] && str[i + 1] != '=')
				return (msg_invalid_id(str, 0), g_status);
		}
	}
	if (i == 0)
		return (msg_invalid_id(str, 0), g_status);
	return (0);
}

int	check_for_option_export(char *str)
{
	if (str[0] == '-')
		return (msg_invalid_option(str, 0), 1);
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
