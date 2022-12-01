/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:25:04 by yanthoma          #+#    #+#             */
/*   Updated: 2022/12/01 01:03:03 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int is_quote(char c)
{
	int i;

	i = 0;
	if ( c == '\"')
		i++;
	else if (c == '\'')
		i++;
	return (i);
}

int next_quote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] = '\"')
			return(i);
		else if(str[i] = '\'')
			return (i);
		i++;		
	}
	return (0);
}


int	is_in_quote(char *str, int pos)
{
	int	i;
	int	sq;
	int	dbq;

	i = 0;
	sq = 0;
	dbq = 0;
	while (str && i <= pos)
	{
		if (sq == 0 && dbq == 0 && str[i] == '\'')
			sq = 1;
		else if (dbq == 0 && sq == 0 && str[i] == '\"')
			dbq = 1;
		else if (sq == 1 && dbq == 0 && str[i] == '\'')
			sq = 0;
		else if (dbq == 1 && sq == 0 && str[i] == '\"')
			dbq = 0;
		i++;
	}
	if (sq == 0 && dbq == 1 && str && str[pos] != '\"')
		return (2);
	else if (sq == 1 && dbq == 0 && str && str[pos] != '\'')
		return (1);
	return (0);
}