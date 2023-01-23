/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:39:48 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/23 18:58:59 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* Cd builtin :
	If PWD= is set, We add "OLD PWD=" in env with the current "PWD=" value.;
	We use chdir to change directory;
	We change the "PWD=" value in env with the current dir, using getcwd.
	Note : if PWD is unset, we just use chdir and env is not modified.
*/

void	cd_err_msg(char *str)
{
	g_var.g_status = 1;
	ft_putstr_fd("minishell: cd: ", 2);
	perror(str);
}

void	update_old_pwd_env(t_envp *envp)
{
	int		oldpwd;
	char	*curr_pwd;

	oldpwd = 0;
	curr_pwd = getcwd(NULL, 0);
	if (!curr_pwd)
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
	{
		free(envp->var[1]);
		envp->var[1] = curr_pwd;
	}
	else
	{
		ft_envpadd_front(&envp, ft_envpnew("OLDPWD=", curr_pwd));
		free(curr_pwd);
	}
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

int	ft_cd(t_data *data)
{
	char	*tmp;
	char	*path;

	g_var.g_status = 0;
	if (!data->args[1] || ft_strcmp(data->args[1], ""))
		return (0);
	if (data->args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2),
			set_err_status(1));
	update_old_pwd_env(data->envp);
	tmp = ft_strjoin("/", data->args[1]);
	if (!tmp)
		return (perror("malloc"), set_err_status(1));
	path = ft_strjoin_spec(getcwd(NULL, 0), tmp);
	if (!path)
		return (perror("malloc"), set_err_status(1));
	if (chdir(path) == -1)
		return (free(tmp), free(path), cd_err_msg(data->args[1]), g_var.g_status);
	update_pwd_env(data->envp);
	return (free(tmp), free(path), g_var.g_status);
}
