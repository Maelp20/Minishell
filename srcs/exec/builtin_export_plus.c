/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_plus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:16:16 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/30 13:18:37 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim_spec(char *s1, char const *set)
{
	char	*dest;
	int		start;
	int		end;
	int		i;

	start = 0;
	while (s1[start] && ft_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_in_set(s1[end - 1], set))
		end--;
	dest = (char *) malloc(sizeof(char) * (end - start + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (start < end)
	{
		dest[i] = s1[start];
		start++;
		i++;
	}
	dest[i] = 0;
	return (free(s1), dest);
}

int	ft_check_plus(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			break ;
	if (str[i - 1] == '+')
		return (1);
	return (0);
}

int	increment_var(t_envp *envp, t_envp *new, t_data *data)
{
	char	*tmp;

	tmp = ft_strdup(envp->var[1]);
	ft_free_dble_array((void **)envp->var);
	envp->var = ft_calloc(sizeof(char **), 3);
	if (!envp->var)
		return (perror("malloc"), clean_exit(data, set_err_status(1)), 1);
	envp->var[0] = ft_strdup(new->var[0]);
	envp->var[1] = ft_strjoin_spec(tmp, new->var[1]);
	envp->var[2] = NULL;
	ft_free_dble_array((void **)new->var);
	free(new);
	return (0);
}
