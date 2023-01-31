/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:05:54 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/30 16:01:18 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	error_pwd_option(char *str)
{
	g_var.g_status = 2;
	ft_putstr_fd("minishell: pwd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": invalid option\n", 2);
}

static void	error_getcwd(void)
{
	g_var.g_status = 1;
	ft_putstr_fd("minishell: pwd: error retrieving current directory: ", 2);
	perror("getcwd: cannot access parent directories");
}

int	ft_pwd(t_data *data)
{
	char	*path;

	g_var.g_status = 0;
	if (data->args[1] && data->args[1][0] == '-')
		return (error_pwd_option(data->args[1]), g_var.g_status);
	path = getcwd(NULL, 0);
	if (!path)
	{
		path = seek_pwd_in_env(data->envp);
		if (!path)
			return (error_getcwd(), g_var.g_status);
	}
	printf("%s\n", path);
	free(path);
	return (g_var.g_status);
}
