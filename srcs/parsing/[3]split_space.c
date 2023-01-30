/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3]split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:25:04 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/30 09:17:24 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_sep(char c)
{
	if (c == '\"')
		return (3);
	else if (c == '\'')
		return (2);
	else if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
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
	tmp = ft_calloc(((len -= i) + 1), sizeof(char));
	if (!tmp)
		return (-2);
	j = -1;
	i--;
	while (input[++i] && --len >= 0)
		tmp[++j] = input[i];
	tmp[++j] = 0;
	lstadd_back_token(lst, lstnew_token2(tmp));
	return (--i);
}

t_tok	*init_token_lst(char *input, t_data	**lst)
{
	int		i;
	t_tok	*tok_lst;

	(void)lst;
	i = 0;
	tok_lst = NULL;
	while (i >= 0 && input[i])
	{
		if (i >= 0 && input[i] && is_sep(input[i]) != 1)
			i = split_space(input, i, &tok_lst);
		i++;
	}
	if (i < 0)
		clean_parsing(&tok_lst, lst);
	return (tok_lst);
}
