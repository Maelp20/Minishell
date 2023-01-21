/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [8]expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:18:55 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/21 13:17:12 by yanthoma         ###   ########.fr       */
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
	while (is_char_var(str[i]))
	{
		i++;
		len++;
	}
	return (len);
}

int	len_expanded(char *str, int len_env, t_data *data)
{
	t_envp	*tmp;
	int		len;

	len = 0;
	tmp = data->envp;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->var[0], len_env))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		len += (int)ft_strlen(tmp->var[1]);
	return (len);
}
