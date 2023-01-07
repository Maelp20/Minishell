/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:25:04 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/04 13:23:56 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


void	clean_dbq(t_tok *lst)
{
	int		i;
	char	*tmp;
	
	i = 1;
	while (lst->token[i] && is_sep(lst->token[i]) != 3)
		i++;
	tmp = ft_strdup(lst->token);
	free (lst->token);
	lst->token = malloc(sizeof(char) * (i + 1));
	if (!lst->token)
		return ;
	i = 0;
	while(is_sep(tmp[++i]) != 3)
		 lst->token[i - 1] = tmp[i];
	lst->token[++i] = '\0';
	free(tmp);
} 


void	clean_sq(t_tok *lst)
{
	int		i;
	char	*tmp;
	
	if (lst->token[1] == '$')
		return ;
	i = 1;
	while (lst->token[i] && is_sep(lst->token[i]) != 2)
		i++;
	tmp = ft_strdup(lst->token);
	free (lst->token);
	lst->token = malloc(sizeof(char) * (i + 1));
	if (!lst->token)
		return ;
	i = 0;
	while(is_sep(tmp[++i]) != 2)
		lst->token[i - 1] = tmp[i];
	lst->token[++i] = '\0';
	free(tmp);
}


void clean_dquotes(t_tok **lst)
{
	t_tok *temp;
	
	temp = *lst;
	while(temp)
	{
		if (temp->token[0] == '\"')
			clean_dbq(temp);
		// if (temp->token[0] == '\'' )
		// 	clean_sq(temp);
		temp = temp->next;
	}
}

void clean_squotes(t_tok **lst)
{
	t_tok *temp;
	
	temp = *lst;
	while(temp)
	{
		// if (temp->token[0] == '\"')
		// 	clean_dbq(temp);
		if (temp->token[0] == '\'' )
			clean_sq(temp);
		temp = temp->next;
	}
}