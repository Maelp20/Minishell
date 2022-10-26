/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:05:54 by mpignet           #+#    #+#             */
/*   Updated: 2022/10/26 16:34:31 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

/* Pwd builtin :
	Before using getcwd, pwd looks into env to see if a PWD path is set. If it is, it returns it.
*/
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

int	ft_pwd(t_envp *envp)
{
	char	*path;
	
	path = seek_pwd_in_env(envp);
	if (!path)
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (perror("getcwd"), 1);
	}
	printf("%s\n", path);
	return (free(path), 0);
}
