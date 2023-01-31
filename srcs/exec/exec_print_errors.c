/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_print_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:11:29 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/31 14:46:57 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	msg_perror(char *str)
{
	g_var.g_status = errno;
	ft_putstr_fd("minishell: ", 2);
	perror(str);
}

void	msg_is_directory(char *str)
{
	g_var.g_status = 126;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}

void	msg_cmd_not_found(char *cmd)
{
	g_var.g_status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	msg_invalid_id(char *str, int i)
{
	g_var.g_status = 1;
	if (!i)
		ft_putstr_fd("minishell: export: `", 2);
	else
		ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

void	msg_invalid_option(char *str, int i)
{
	g_var.g_status = 2;
	if (!i)
		ft_putstr_fd("minishell: export: `", 2);
	else
		ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': invalid option\n", 2);
}
