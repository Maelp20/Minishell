/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:05:54 by mpignet           #+#    #+#             */
/*   Updated: 2022/12/07 15:20:08 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/* Pwd builtin :
	Before using getcwd, pwd looks into env to see if a PWD path is set. If it is, it returns it.
*/

int	ft_pwd(t_data *data)
{
	char	*path;

	if (data->args[1] && data->args[1][0] == '-')
		return (ft_putstr_fd("minishell: pwd: invalid option", 2) , 1);
	path = seek_pwd_in_env(data->envp);
	if (!path)
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (perror("getcwd"), 1);
	}
	printf("%s\n", path);
	return (free(path), 0);
}
