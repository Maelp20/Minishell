/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:05:54 by mpignet           #+#    #+#             */
/*   Updated: 2022/10/25 16:42:44 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

/* Pwd builtin :
	Before using getcwd, pwd looks into env to see if a PWD path is set. If it is, it returns it.
*/
char *seek_pwd_in_env(char **envp)
{
	char	*pwd_line;
	int		i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		pwd_line = ft_strnstr(envp[i], "PWD=", 4);
		if (pwd_line)
		{
			pwd_line = ft_substr(envp[i], 4, ft_strlen(envp[i]));
			if (!pwd_line)
				return (perror("Malloc"), NULL);
			break ;
		}
		i++;
	}
	return (pwd_line);
}

int	ft_pwd(char **envp)
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

/* pour EXIT builtin :
	ATTENTION : la valeur de retour sera entre 0 et 255. exit doit tout nettoyer (free et close).
 */