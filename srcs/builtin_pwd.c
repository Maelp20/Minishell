/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:05:54 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/04 16:58:05 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

/* Pwd builtin :
	Before using getcwd, pwd looks into env to see if a PWD path is set. If it is, it returns it.
*/

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
