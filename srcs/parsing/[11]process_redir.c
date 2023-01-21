/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [11]process_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:24:09 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/21 13:15:13 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	process_redir(t_tok **lst, t_data **data)
{
	t_tok	*temp_tok;
	t_data	*temp_data;

	temp_tok = *lst;
	temp_data = *data;
	while (lst && temp_tok && !ft_strcmp(temp_tok->token, "|"))
	{
		if (lst && !check_redir(lst, &temp_tok, data, temp_data))
			temp_tok = temp_tok->next;
		else
			temp_tok = *lst;
	}
}
