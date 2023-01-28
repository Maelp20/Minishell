/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:36:34 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/28 17:27:30 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_wait(t_data *data)
{
	int	status;

	(void)data;
	while (wait(&status) != -1)
	{
		g_var.g_status = WEXITSTATUS(status);
		continue ;
	}
}

void	ft_envpclear(t_envp **envp)
{
	t_envp	*tmp;

	while (*envp)
	{
		tmp = *envp;
		*envp = (*envp)->next;
		if (tmp->var)
			ft_free_dble_array((void **)tmp->var);
		free(tmp);
	}
}

int	ft_data_size(t_data *data)
{
	int	nb;

	nb = 0;
	if (!data)
		return (0);
	while (data)
	{
		nb++;
		data = data->next;
	}
	return (nb);
}

int	ft_strcmp_spec(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	ls1;
	int	ls2;

	if (!s1 || !s2)
		return (0);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	if (ls1 != ls2)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
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