/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [9]clean_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:25:04 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/27 12:48:06 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	del_dollard(t_tok *lst, int i)
{
	int	j;

	j = i;
	lst->token[i] = lst->token[i + 1];
	i++;
	while (lst->token[j + 1])
	{
		lst->token[j] = lst->token [j + 1];
		j++;
	}
	lst->token[j] = 0;
	return (i -1);
}

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

int	trigger_del_dollard(char *token, int i)
{
	if (token[i] == '$' && (token[i + 1] == '\"' || token[i + 1] == '\''))
		return (1);
	return (0);
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
		while (temp->token && temp->token[i])
		{
			if (temp->token[i] == '\"')
				i = clean_dbq(temp, i);
			if (temp->token[i] == '\'' )
				i = clean_sq(temp, i);
			if (trigger_del_dollard(temp->token, i))
				i = del_dollard(temp, i);
			if (temp->token[i] != '\'' && temp->token[i] != '\"' )
				i++;
		}
		temp->token[i] = 0;
		temp = temp->next;
	}
}
