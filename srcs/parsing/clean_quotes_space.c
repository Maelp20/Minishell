/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:25:04 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/17 18:44:35 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


int	clean_dbq(t_tok *lst, int i)
{
	if (i == 0)
		lst->token[i] = lst->token[i + 1];
	i++;
	while (lst->token[i] && is_sep(lst->token[i]) != 3)
	{
		printf("db %c\n", lst->token[i]);
		lst->token[i - 1] = lst->token[i];
		i++;
	}
	lst->token[i] = lst->token[i + 1];
	return (i);
} 


int	clean_sq(t_tok *lst, int i)
{
	if (i == 0)
		lst->token[i] = lst->token[i + 1];
	i++;
	while (lst->token[i] && is_sep(lst->token[i]) != 2)
	{
		lst->token[i - 1] = lst->token[i];
		i++;
	}
	lst->token[i] = lst->token[i + 1];
	return (i);
}



void clean_quotes(t_tok **lst)
{
	t_tok	*temp;
	int 	i;
	
	i = 0;
	temp = *lst;
	while(temp)
	{
		while (temp->token[i])
		{
			if (temp->token[i] == '\"')
		 		i = clean_dbq(temp, i);
			if (temp->token[i] == '\'' )
				i = clean_sq(temp, i);
			i++;
		}
		temp->token[i] = '\0';
		temp = temp->next;
	}
}