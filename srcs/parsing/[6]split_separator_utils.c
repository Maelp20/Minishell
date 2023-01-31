/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [6]split_separator_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:29:20 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/31 02:35:10 by yanthoma         ###   ########.fr       */
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

int	skip_separator(char *token, int i)
{
	if (is_separator(token[i], token[i + 1]) == 2)
		i += 2;
	else if (is_separator(token[i], token[i + 1]) == 1)
		i += 1;
	return (i);
}

int	skip_non_separator(char *token, int i)
{
	while (token[i] && check_separator(token[i]) == 0)
		i++;
	return (i);
}

int	countword(char *token)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] && (token[i] == '\'' || token[i] == '\"'))
		{
			i = skip_quote(token, i);
			j++;
		}
		else if (token[i] && !check_separator(token[i]))
		{
			i = skip_non_separator(token, i);
			j++;
		}
		else
		{
			i = skip_separator(token, i);
			j++;
		}
	}
	return (j);
}
