/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:59:21 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/29 17:29:19 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_dble_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	count_equal_signs(char *arg)
{
	int	i;
	int	nb;

	i = -1;
	nb = 0;
	while (arg[++i])
		if (arg[i] == '=')
			nb++;
	return (nb);
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

char	*ft_strjoin_free_s2(char *s1, char *s2)
{
	char	*dest;
	int		len;
	int		i;
	int		j;

	if (!s2)
	{
		s2 = ft_calloc(sizeof(char), 1);
		if (!s2)
			return (NULL);
	}
	if (!s1)
		return (free(s2), NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (free(s2), NULL);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (free(s2), dest);
}
