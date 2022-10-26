/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:53:33 by mpignet           #+#    #+#             */
/*   Updated: 2022/10/26 15:59:28 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	ft_env(t_envp *envp)
{
	while (envp->var)
	{
		printf("%s", envp->var[0]);
		printf("%s\n", envp->var[1]);
		envp = envp->next;
	}
}