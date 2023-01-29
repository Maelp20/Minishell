/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:53:52 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/29 16:54:14 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	cd_err_msg(char *str)
{
	g_var.g_status = 1;
	ft_putstr_fd("minishell: cd: ", 2);
	perror(str);
}

void	update_old_pwd_env(t_envp *envp, char *curr_pwd)
{
	int		oldpwd;
	t_envp	*start;

	oldpwd = 0;
	start = envp;
	if (!curr_pwd)
		return ;
	while (envp)
	{
		if (ft_strnstr(envp->var[0], "OLDPWD=", 7))
		{
			oldpwd = 1;
			break ;
		}
		envp = envp->next;
	}
	if (oldpwd)
	{
		free(envp->var[1]);
		envp->var[1] = curr_pwd;
	}
	else
		ft_envpadd_back(&start, ft_envpnew("OLDPWD=", curr_pwd));
}

void	update_pwd_env(t_envp *envp)
{
	if (!envp)
		return ;
	while (envp)
	{
		if (ft_strnstr(envp->var[0], "PWD=", 4))
			break ;
		envp = envp->next;
	}
	if (envp == NULL)
		return ;
	free(envp->var[1]);
	envp->var[1] = getcwd(NULL, 0);
}
