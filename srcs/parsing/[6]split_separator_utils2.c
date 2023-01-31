/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [6]split_separator_utils2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:31:55 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/31 02:34:52 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	countlen_word(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] && (token[i] == '\'' || token[i] == '\"'))
			i = skip_quote(token, i);
		else if (token[i] && !check_separator(token[i]))
			i = skip_non_separator(token, i);
		if (i > 0)
			return (i);
		else
			return (i = skip_separator(token, i));
	}
	return (i);
}

int	skip_quote(char *token, int i)
{
	char	quote;

	quote = token[i];
	i++;
	while (token[i] && token[i] != quote)
	{
		i++;
	}	
	if (token[i] == '\0')
		return (i);
	return (i + 1);
}

int	has_a_sep(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '\"')
			i = skip_quote(token, i);
		else if (token[i] == '>' || token[i] == '<' || token [i] == '|')
			return (1);
		else if (token[i] == '\'' || token[i] == '\"')
			;
		else
			i++;
	}
	return (0);
}
