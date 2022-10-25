/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:39:48 by mpignet           #+#    #+#             */
/*   Updated: 2022/10/24 19:04:04 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/* Cd builtin :
	Using chdir to change directory... could it be that simple ?
	DOUBT
	ATTENTION : CD changes env in order to redefine the current directory (line "PWD=" in env);
		Don4t forget to add "OLD PWD=" in env after the change.
*/
int	ft_cd(t_lst *cmd)
{
	int	i;
	char s[100];

	// printf("%s\n", getcwd(s, 100));
	i = chdir(cmd->args[0]);
	// printf("%s\n", getcwd(s, 100));
	return (i);
}