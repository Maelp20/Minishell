/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:05:54 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/20 17:28:28 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* Pwd builtin :
	Before using getcwd, pwd looks into env to see if a PWD path is set.
	If it is, it returns it.
*/

int	ft_pwd(t_data *data)
{
	char	*path;

	err_status = 0;
	if (data->args[1] && data->args[1][0] == '-')
		return (ft_putstr_fd("minishell: pwd: invalid option", 2),
				set_err_status(127));
	path = getcwd(NULL, 0);
	if (!path)
	{
		path = seek_pwd_in_env(data->envp);
		if (!path)
			return (perror("minishell: pwd"), set_err_status(1));
	}
	printf("%s\n", path);
	free(path);
	return (err_status);
}
