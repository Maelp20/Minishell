/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:11:29 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/23 19:32:28 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	msg_no_such_file(char *str)
{
	g_var.g_status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("no such file or directory: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	msg_cmd_not_found(char *cmd)
{
	g_var.g_status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	msg_export_err(char *str)
{
	g_var.g_status = 1;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

void	msg_unset_err(char *str)
{
	g_var.g_status = 1;
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

void	msg_unset_option(char *str)
{
	g_var.g_status = 1;
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': invalid option\n", 2);
}

void	msg_export_option(char *str)
{
	g_var.g_status = 1;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': invalid option\n", 2);
}
