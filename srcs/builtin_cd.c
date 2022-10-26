/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:39:48 by mpignet           #+#    #+#             */
/*   Updated: 2022/10/26 16:36:46 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

/* Cd builtin :
	Using chdir to change directory.
	We change env in order to redefine the current directory (line "PWD=" in env);
	We also add "OLD PWD=" in env after the change.
*/

void	update_old_pwd_env(t_envp *envp)
{
	int	oldpwd;

	oldpwd = 0;
	while (envp->var)
	{
		if (ft_strnstr(envp->var[0], "OLD PWD=", 8))
		{
			oldpwd = 1;
			break ;
		}
		envp = envp->next;		
	}
	if (oldpwd)
		envp->var[1] = getcwd(NULL, 0);
	else
		ft_envpadd_back(&envp, ft_envpnew("OLD PWD=", getcwd(NULL, 0)));
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
	envp->var[1] = getcwd(NULL, 0);
}

int	ft_cd(t_cmd *cmd, t_envp *envp)
{
	int	i;

	update_old_pwd_env(envp);
	i = chdir(cmd->args[1]);
	update_pwd_env(envp);
	// printf("%s\n", getcwd(NULL, 0));
	return (i);
}