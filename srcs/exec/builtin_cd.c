/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:39:48 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/27 19:46:29 by mpignet          ###   ########.fr       */
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

static int	ft_change_dir(t_data *data, char *path, char *curr_pwd, char *tmp)
{
	if (chdir(path) == -1)
		return (free(tmp), free(path), free(curr_pwd),
			cd_err_msg(data->args[1]), g_var.g_status);
	update_old_pwd_env(data->envp, curr_pwd);
	update_pwd_env(data->envp);
	return (free(tmp), free(path), g_var.g_status);
}

int	ft_cd(t_data *data)
{
	char	*tmp;
	char	*path;
	char	*curr_pwd;

	g_var.g_status = 0;
	if (!data->args[1] || ft_strcmp(data->args[1], ""))
		return (0);
	if (data->args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2),
			set_err_status(1));
	curr_pwd = getcwd(NULL, 0);
	if (!curr_pwd)
		return (cd_err_msg(data->args[1]), g_var.g_status);
	tmp = ft_strjoin("/", data->args[1]);
	if (!tmp)
		return (perror("malloc"), free(curr_pwd),
			clean_exit(data, set_err_status(1)), 1);
	path = ft_strjoin_spec(getcwd(NULL, 0), tmp);
	if (!path)
		return (perror("malloc"), free(curr_pwd), free(tmp),
			clean_exit(data, set_err_status(1)), 1);
	return (ft_change_dir(data, path, curr_pwd, tmp));
}
