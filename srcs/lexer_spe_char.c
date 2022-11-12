/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_spe_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:25:04 by yanthoma          #+#    #+#             */
/*   Updated: 2022/11/12 12:42:17 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

int	is_in_quote(char *arg)
{
	int	i;
	int	dbq;
	int	q;
	
	i = 0;
	dbq = 0;
	q = 0;
	while (arg[i])
	{
		if (arg[i] == '\"' && dbq == 0 && q < 2)
			dbq++;
		else if (arg[i] == '\'' && dbq == 0)
			q++;
		else if (arg[i] == '\"' && dbq == 1)
			return (1);
		else if (arg[i])
		
	}
	return(0);
}