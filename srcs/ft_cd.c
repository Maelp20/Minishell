/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:39:48 by mpignet           #+#    #+#             */
/*   Updated: 2022/10/25 16:30:54 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

/* Cd builtin :
	Using chdir to change directory... could it be that simple ?
	DOUBT
	ATTENTION : CD changes env in order to redefine the current directory (line "PWD=" in env);
		Don't forget to add "OLD PWD=" in env after the change.
*/
int	ft_cd(t_lst *cmd)
{
	int	i;

	// printf("%s\n", getcwd(NULL, 0));
	i = chdir(cmd->args[1]);
	// printf("%s\n", getcwd(NULL, 0));
	return (i);
}