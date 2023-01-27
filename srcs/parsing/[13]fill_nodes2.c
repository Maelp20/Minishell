/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [13]fill_nodes2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:55:35 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/27 22:57:34 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	trigger_creation(int *i, t_tok *temp, t_data *data_tmp)
{
	while (temp && !ft_strcmp(temp->token, "|"))
	{
		(*i)++;
		temp = temp->next;
	}
	if (*i == 0)
		return ;
	data_tmp->args = ft_calloc((*i) + 1, sizeof(char *));
}
