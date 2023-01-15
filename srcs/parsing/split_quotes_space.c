/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:25:04 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/15 14:39:52 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_sep(char c)
{
	if (c == '\"') 
		return (3);
	else if ( c == '\'')
		return (2);
	else if ( c == ' ')
		return (1);
	return (0);
}

int	split_dbq(char *input, int i, t_tok **lst)
{
	int		j;
	char	*tmp;
	
	j = i;
	while (input[j + 1] && is_sep(input[j]) != 3)
		j++;
	if (input[j] != '\"' && input [j + 1] =='\0')
		return (-2);
	tmp = malloc(sizeof(char) * (j - i + 3));
	if (!tmp)
		return (-2);
	j = 0;
	i--;
	tmp[j] = '\"';
	while(is_sep(input[++i]) != 3)
		tmp[++j] = input[i];
	tmp[++j] = '\"';
	tmp[++j] = '\0';
	lstadd_back_token(lst, lstnew_token(tmp));
	return (free(tmp), ++i);
} 

int	split_sq(char *input, int i, t_tok **lst)
{
	int		j;
	char	*tmp;

	j = i;
	while (is_sep(input[j]) != 2 && input[j + 1]) 
		j++;
	if (input[j] != '\'' && input [j + 1] =='\0')
		return (-2);
	tmp = malloc(sizeof(char) * (j - i + 3));
	if (!tmp)
		return (-2);
	j = 0;
	i--;
	tmp[j] = '\'';
	while(is_sep(input[++i]) != 2)
		tmp[++j] = input[i];
	tmp[++j] = '\'';
	tmp[++j] = '\0';
	lstadd_back_token(lst, lstnew_token(tmp));
	return (free(tmp), ++i);
}

int	split_space(char *input, int i, t_tok **lst)
{
	int		j;
	int		len;
	char	*tmp;

	len = i;
	while (input[len] && is_sep(input[len]) != 1)
	{
		if (is_sep(input[len++]) >= 2)
		{
			while (input[len] && is_sep(input[len]) < 2)
				len++;
			len++;
		}
	}
	tmp = malloc(sizeof(char) * ((len -= i) + 1));
	if (!tmp)
		return (-2);
	j = -1;
	i--;git add -A
	while (input[++i] && --len >= 0)
		tmp[++j] = input[i];
	tmp[++j] = '\0';
	lstadd_back_token(lst, lstnew_token(tmp));
	return (free(tmp), --i);
}
