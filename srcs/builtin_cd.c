/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:39:48 by mpignet           #+#    #+#             */
/*   Updated: 2022/11/14 18:34:04 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* Cd builtin :
	If PWD= is set, We add "OLD PWD=" in env with the current "PWD=" value.;
	We use chdir to change directory;
	We change the "PWD=" value in env with the current dir, using getcwd.
	Note : if PWD is unset, we just use chdir and env is not modified.
*/

void	update_old_pwd_env(t_envp *envp)
{
	int	oldpwd;
	char *curr_pwd;

	oldpwd = 0;
	curr_pwd = seek_pwd_in_env(envp);
	if (!curr_pwd)
		return ;
	while (envp->var)
	{
		if (ft_strnstr(envp->var[0], "OLDPWD=", 7))
		{
			oldpwd = 1;
			break ;
		}
		envp = envp->next;		
	}
	if (oldpwd)
		envp->var[1] = curr_pwd;
	else
		ft_envpadd_back(&envp, ft_envpnew("OLDPWD=", curr_pwd));
}

void	update_pwd_env(t_envp *envp)
{
	if (!envp)
		return ;
	while (envp->var)
	{
		if (ft_strnstr(envp->var[0], "PWD=", 4))
			break ;
		envp = envp->next;
	}
	if (envp == NULL)
		return ;
	envp->var[1] = getcwd(NULL, 0);
}

int	ft_cd(t_data *cmd)
{
	int	i;

	update_old_pwd_env(cmd->envp);
	i = chdir(cmd->args[1]);
	update_pwd_env(envp);
	return (i);
}