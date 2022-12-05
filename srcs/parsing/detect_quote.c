/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:25:04 by yanthoma          #+#    #+#             */
/*   Updated: 2022/11/14 18:28:19 by mpignet          ###   ########.fr       */
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

int	is_in_quote(char *arg, int i)
{
	int	dbq;
	int	q;
	int l;
	
	l = i;
	dbq = 0;
	q = 0;
	
	while (arg[l] && dbq != 2 && q != 2)
	{
		if (arg[l] == '\"' && dbq == 0 && q == 0)
			dbq++;
		else if (arg[l] == '\'' && dbq == 0 && q ==0 )
			q++;
		else if (arg[l] == '\"' && dbq == 1)
			dbq++;
		else if (arg[l] == '\'' && q == 1)
			q++;
		printf(" char2 %c\n", arg[l]);
		l++;
	}
	printf("l = %d\n", l - i);
	if (dbq == 2 || q == 2)
		return(l - i);
	else
		return (0);
}
