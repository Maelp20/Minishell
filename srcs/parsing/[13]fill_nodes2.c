/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [13]fill_nodes2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:55:35 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/31 03:22:50 by yanthoma         ###   ########.fr       */
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

void	process_pipes(t_tok *temp, t_tok **lst, t_data *data_tmp)
{
	process_node(&temp, &(*lst));
	data_tmp->out_pipe = 1;
	if (data_tmp->next)
		data_tmp->next->in_pipe = 1;
}
