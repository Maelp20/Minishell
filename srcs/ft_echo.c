/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:31:20 by mpignet           #+#    #+#             */
/*   Updated: 2022/10/25 16:19:02 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

/* Echo builtin :
	1 - checks if flag "-n" is present
	(note that the bash command integrates "-n" or "-nn", "-nnnnn" etc as valid flags, 
	and they can be multiples. Ex : command "echo -n -nnn -n Lol" just prints "Lol".)
	2 - We print everything after the flag (or flags).
	3 - If there wasn't any valid flags before the strings to print, we print a newline.
*/

int	is_valid_flag(char *str)
{
	int	i;

	i = 0;
	if(str[0] == '-')
	{
		while (str[++i])
			if (str[i] != 'n')
				return (0);
		return (1);
	}
	return (0);
}

int	ft_echo(t_lst *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd->args[i] && is_valid_flag(cmd->args[i]))
	{
		flag = 1;
		i++;
	}
	while (cmd->args[i + 1])
		printf("%s ", cmd->args[i++]);
	printf("%s", cmd->args[i]);
	if (flag == 0)
		printf("\n");
	return (0);
}
