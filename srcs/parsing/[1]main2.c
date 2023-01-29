/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]main2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:37:41 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/30 00:32:48 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	pars_token(t_tok *lst, t_data *data)
{
	clean_token(&lst);
	expand(&lst, &data);
	clean_quotes(&lst);
}

void	o_signal(t_data *data)
{
	printf("exit\n");
	clean_exit(data, 0);
}
