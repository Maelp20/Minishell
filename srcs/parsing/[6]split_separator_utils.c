/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [6]split_separator_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:29:20 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/21 13:16:55 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_separator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	is_separator(char c1, char c2)
{
	if (c2 && ((c1 == '>' && c2 == '>') || (c1 == '<' && c2 == '<')))
		return (2);
	else if (c1 == '>' || c1 == '<' || c1 == '|')
		return (1);
	return (0);
}

int	has_a_sep(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '>' || token[i] == '<' || token [i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	countword(char *token)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (token[i])
	{
		if (!check_separator(token[i]))
		{
			j++;
			while (token[i] && !check_separator(token[i]))
				i++;
		}
		else
		{
			j++;
			if (is_separator(token[i], token[i + 1]) == 2)
				i += 2;
			else if (is_separator(token[i], token[i + 1]) == 1)
				i += 1;
		}
	}
	return (j);
}
