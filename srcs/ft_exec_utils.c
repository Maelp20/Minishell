/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:36:34 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/11 17:00:51 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"


t_envp	*ft_envplast(t_envp *envp)
{
	if (!envp)
		return (0);
	while (envp->next)
		envp = envp->next;
	return (envp);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;

	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

t_envp	*ft_envpnew(char *var, char *value)
{
	t_envp	*new;

	new = (t_envp *)malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->var[0] = var;
	new->var[1] = value;
	new->next = NULL;
	return (new);
}

t_envp	*ft_envplast(t_envp *envp)
{
	if (!envp)
		return (0);
	while (envp->next)
		envp = envp->next;
	return (envp);
}

void	ft_envpadd_back(t_envp **envp, t_envp *new)
{
	t_envp	*tmp;

	if (!envp)
		return ;
	if (!*envp)
		*envp = new;
	else
	{
		tmp = ft_envplast(*envp);
		tmp->next = new;
	}
}

char	*seek_var_in_env(t_envp *envp, char *var)
{
	char	*var_line;
	char	*needle;

	needle = ft_strjoin(var, "=");
	if (!needle || !envp)
		return (NULL);
	while (envp->var)
	{
		var_line = ft_strnstr(envp->var[0], needle, ft_strlen(needle));
		if (var_line)
		{
			var_line = ft_strjoin(envp->var[0], envp->var[1]);
			if (!var_line)
				return (perror("Malloc"), NULL);
			break ;
		}
		envp = envp->next;
	}
	return (var_line);
}

char *seek_pwd_in_env(t_envp *envp)
{
	char	*pwd_line;

	if (!envp)
		return (NULL);
	while (envp->var)
	{
		pwd_line = ft_strnstr(envp->var[0], "PWD=", 4);
		if (pwd_line)
			break ;
		envp=envp->next;
	}
	if (!pwd_line)
		return (NULL);
	return (envp->var[1]);
}