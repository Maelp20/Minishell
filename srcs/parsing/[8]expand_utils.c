/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [8]expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:18:55 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/23 20:38:12 by yanthoma         ###   ########.fr       */
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
	printf("len env%s\n", str);
	if (*str +1 == '?')
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

	len = 0;
	tmp = data->envp;
	printf("len expanded str = %s\n", str);
	if (*str == '?')
		return(len_status(g_var.g_status));
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
