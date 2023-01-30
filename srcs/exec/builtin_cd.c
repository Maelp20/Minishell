/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:39:48 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/30 15:29:52 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	chdir_err_msg(char *str)
{
	g_var.g_status = 1;
	ft_putstr_fd("minishell: chdir: ", 2);
	perror(str);
}

static int	ft_change_dir(t_data *data, char *path, char *curr_pwd)
{
	if (chdir(path) == -1)
		return (free(path), free(curr_pwd),
			chdir_err_msg(data->args[1]), g_var.g_status);
	update_old_pwd_env(data->envp, curr_pwd);
	update_pwd_env(data->envp);
	return (free(path), g_var.g_status);
}

char	*prepare_path(t_data *data)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin("/", data->args[1]);
	if (!tmp)
		return (perror("malloc"), clean_exit(data, set_err_status(1)), NULL);
	path = ft_strjoin_spec(getcwd(NULL, 0), tmp);
	if (!path)
		return (perror("malloc"), free(tmp),
			clean_exit(data, set_err_status(1)), NULL);
	return (free(tmp), path);
}

int	go_home(t_data *data)
{
	char	*curr_pwd;

	curr_pwd = getcwd(NULL, 0);
	if (!curr_pwd)
		return (cd_err_msg(data->args[1]), g_var.g_status);
	if (chdir("/mnt/nfs/homes/mpignet") == -1)
		return (cd_err_msg(data->args[1]), g_var.g_status);
	update_old_pwd_env(data->envp, curr_pwd);
	update_pwd_env(data->envp);
	return (g_var.g_status);
}

int	ft_cd(t_data *data)
{
	char	*path;
	char	*curr_pwd;

	g_var.g_status = 0;
	if ((!data->args[1] || ft_strcmp(data->args[1], "")))
		return (go_home(data), g_var.g_status);
	if (data->args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2),
			set_err_status(1));
	curr_pwd = getcwd(NULL, 0);
	if (!curr_pwd)
		return (cd_err_msg(data->args[1]), g_var.g_status);
	if (data->args[1][0] == '/')
		path = ft_strdup(data->args[1]);
	else
		path = prepare_path(data);
	return (ft_change_dir(data, path, curr_pwd), 0);
}
