/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:10:01 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/25 20:20:19 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_for_option(char *str)
{
	if (str[0] == '-')
		return (msg_invalid_option(str, 1), 1);
	return (0);
}

int	check_valid_identifier_unset(char *str)
{
	char	*invalid;
	int		i;
	int		j;

	invalid = "!@#$%^&*()`~-|[]{};:,./<>?";
	if (ft_strcmp(str, "="))
		return (msg_invalid_id(str, 1), g_status);
	if (str[0] >= '0' && str[0] <= '9')
		return (msg_invalid_id(str, 1), g_status);
	i = -1;
	while (str[++i] && str[i] != '=')
	{
		j = -1;
		while (invalid[++j])
		{
			if (invalid[j] == str[i])
				return (msg_invalid_id(str, 1), g_status);
			if (str[i] == '+' && str[i + 1] && str[i + 1] != '=')
				return (msg_invalid_id(str, 1), g_status);
		}
	}
	if (i == 0)
		return (msg_invalid_id(str, 1), g_status);
	return (0);
}

void	delete_var_from_env(t_data *data, char *var)
{
	t_envp	*tmp;

	while (data->envp->next)
	{
		if (ft_strnstr(data->envp->next->var[0], var, ft_strlen(var)))
		{
			tmp = data->envp->next;
			ft_free_dble_array((void **)data->envp->next->var);
			data->envp->next = data->envp->next->next;
			free(tmp);
			break ;
		}
		data->envp = data->envp->next;
	}	
}

int	ft_unset(t_data *data)
{
	char	*var;
	t_envp	*first_node;
	int		i;

	g_status = 0;
	i = -1;
	if (!data->envp || !data->args[1] || check_for_option(data->args[1]))
		return (g_status);
	while (data->args[++i])
	{
		if (check_valid_identifier_unset(data->args[i]))
			continue ;
		var = ft_strjoin(data->args[i], "=");
		if (!var)
			return (perror("malloc"), clean_exit(data, set_err_status(1)), 1);
		first_node = data->envp;
		delete_var_from_env(data, var);
		free(var);
		data->envp = first_node;
	}
	return (0);
}
