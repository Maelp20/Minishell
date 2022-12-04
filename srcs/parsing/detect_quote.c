/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:25:04 by yanthoma          #+#    #+#             */
/*   Updated: 2022/12/04 17:05:52 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_quote(char c)
{
	if (c == '\"')
		return (2);
	else if ( c == '\'')
		return (1);
	return (0);
}

int	split_dbq(char *input, int i, t_tok **lst)
{
	int		j;
	char	*tmp;
	
	j = i;
	while (is_quote(input[j]) != 2 && input[j + 1])
		j++;
	if (input[j] != '\"' && input [j + 1] =='\0')
		return (-2);
	tmp = malloc(sizeof(char) * (j + 1));
	if (!tmp)
		return (0);
	j = -1;
	i--;
	while(is_quote(input[++i]) != 2)
		tmp[++j] = input[i];
	tmp[++j] = '\0';
	lstadd_back_token(lst, lstnew_token(tmp));
	return (free(tmp), ++i);
} 

int	split_sq(char *input, int i, t_tok **lst)
{
	int		j;
	char	*tmp;
	
	j = i;
	while (is_quote(input[j]) != 1 && input[j + 1])
		j++;
	if (input[j] != '\'' && input [j + 1] =='\0')
		return (-2);
	tmp = malloc(sizeof(char) * (j + 1));
	if (!tmp)
		return (0);
	j = -1;
	i--;
	while(is_quote(input[++i]) != 2)
		tmp[++j] = input[i];
	tmp[++j] = '\0';
	lstadd_back_token(lst, lstnew_token(tmp));
	return (free(tmp), ++i);
}