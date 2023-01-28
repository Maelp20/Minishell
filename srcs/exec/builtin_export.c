/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:37:16 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/28 17:49:54 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* int	var_already_exists(t_envp *envp, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
	if (!envp)
		return (NULL);
	while (envp)
	{
		if (ft_strcmp(envp->var[0], arg))
			return (1);
		envp = envp->next;
	}
	return (0);
} */

int	ft_dble_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	replace_var_in_env(t_envp *envp, t_envp *new, t_data *data)
{
	if (!new || !envp)
		return (0);
	while (envp)
	{
		if (ft_strnstr(envp->var[0], new->var[0], ft_strlen(new->var[0])))
		{
			ft_free_dble_array((void **)envp->var);
			envp->var = ft_calloc(sizeof(char **), 3);
			if (!envp->var)
				return (perror("malloc"), clean_exit(data, set_err_status(1)),
					1);
			envp->var[0] = ft_strdup(new->var[0]);
			envp->var[1] = ft_strdup(new->var[1]);
			envp->var[2] = NULL;
			ft_free_dble_array((void **)new->var);
			free(new);
			return (1);
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
		return (msg_invalid_option(str, 0), g_var.g_status);
	return (0);
}

/* int	check_if_value(char	*str)
{
	int	i;

	i = -1;
	while(str[++i])
		if(str[i] == '=')
			return (1);
	return (0);
} */

int	count_equal_signs(char *arg)
{
	int	i;
	int nb;
	
	i = -1;
	nb = 0;
	while (arg[++i])
		if (arg[i] == '=')
			nb++;
	return (nb);
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
			return (perror("malloc"), clean_exit(data, set_err_status(1)), NULL);
	}
	else
	{
		new->var = ft_calloc(sizeof(char *), 2);
		if (!new->var)
		return (perror("malloc"), clean_exit(data, set_err_status(1)), NULL);
		new->var[0] = ft_strdup(arg);
		new->var[1] = NULL;
		count++;
	}
	new->var[0] = ft_strjoin_spec(new->var[0], "=");
	if (!new->var[0])
		return (perror("malloc"), clean_exit(data, set_err_status(1)), NULL);
	while (--count > 0)
		new->var[1] = ft_strjoin_free_s2("=", new->var[1]);
	return (new);
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
