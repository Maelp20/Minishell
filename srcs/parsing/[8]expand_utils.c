/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [8]expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:18:55 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/25 20:44:51 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_char_var(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	len_env(char *str, int i)
{
	int	len;

	len = 0;
	if ((str[i]) == '?')
		return (1);
	while (is_char_var(str[i]))
	{
		i++;
		len++;
	}
	return (len);
}

int len_status(int status)
{
	int	len;

	len = 0;
	if (status == 0)
		return (1);
	while (status)
	{
		status /= 10;
		len++;
	}
	return (len);
}

int	len_expanded(char *str, int len_env, t_data *data)
{
	t_envp	*tmp;
	int		len;
	int comp_len;

	len = 0;
	tmp = data->envp;
	if (*str == '?')
		return(len_status(g_status));
	while (tmp)
	{
		comp_len = (int)ft_strlen(tmp->var[0]) - 1;
		if (len_env == comp_len && ft_strncmp(str, tmp->var[0], len_env) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		len += (int)ft_strlen(tmp->var[1]);
	return (len);
}
