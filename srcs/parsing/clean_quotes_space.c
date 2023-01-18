/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:25:04 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/18 03:09:51 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	clean_dbq(t_tok *lst, int i)
{
	int	j;

	if (i == 0)
		lst->token[i] = lst->token[i + 1];
	i++;
	while (lst->token[i] && is_sep(lst->token[i]) != 3)
	{
		lst->token[i - 1] = lst->token[i];
		i++;
	}
	j = i;
	lst->token[j - 1] = lst->token[j];
	lst->token[j] = lst->token[j + 1];
	while (lst->token[j + 1])
	{
		lst->token[j - 1] = lst->token [j + 1];
		j++;
	}
	lst->token[j - 1] = 0;
	return (i - 1);
}

int	clean_sq(t_tok *lst, int i)
{
	int	j;

	if (i == 0)
		lst->token[i] = lst->token[i + 1];
	i++;
	while (lst->token[i] && is_sep(lst->token[i]) != 2)
	{
		lst->token[i - 1] = lst->token[i];
		i++;
	}
	j = i;
	lst->token[j - 1] = lst->token[j];
	lst->token[j] = lst->token[j + 1];
	while (lst->token[j + 1])
	{
		lst->token[j - 1] = lst->token [j + 1];
		j++;
	}
	lst->token[j -1] = 0;
	return (i - 1);
}

void	clean_quotes(t_tok **lst)
{
	t_tok	*temp;
	int		i;

	i = 0;
	temp = *lst;
	while (temp)
	{
		i = 0;
		while (temp->token[i])
		{
			if (temp->token[i] == '\"')
				i = clean_dbq(temp, i);
			if (temp->token[i] == '\'' )
				i = clean_sq(temp, i);
			if (temp->token[i] != '\'' && temp->token[i] != '\"' )
				i++;
		}
		temp->token[i] = '\0';
		temp = temp->next;
	}
}
