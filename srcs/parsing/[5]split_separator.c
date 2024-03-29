/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [5]split_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:58:23 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/31 13:18:02 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*fill_word(char *token, int len)
{
	int		i;
	char	*split;

	i = 0;
	split = malloc(sizeof(char) * (len + 1));
	while (token [i] && i < len)
	{
		split[i] = token[i];
		i++;
	}
	split[i] = '\0';
	return (split);
}

int	len_word(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (!check_separator(token[i]))
		{
			while (token[i] && !check_separator(token[i]))
				i++;
			return (i);
		}
		else
		{
			if (is_separator(token[i], token[i + 1]) == 2)
				i += 2;
			else if (is_separator(token[i], token[i + 1]) == 1)
				i += 1;
			return (i);
		}
	}
	return (i);
}

char	**extract(char *token)
{
	int		nb_word;
	char	**extracted;
	int		i;
	int		len;

	i = 0;
	nb_word = countword(token);
	extracted = ft_calloc(nb_word + 1, sizeof(char *));
	if (!extracted)
		return (NULL);
	while (i < nb_word)
	{
		len = countlen_word(token);
		extracted[i] = fill_word(token, len);
		token += len;
		i++;
	}
	extracted[i] = 0;
	return (extracted);
}

int	split_sep(t_tok *lst, t_tok **head, t_data *data)
{
	char	**splitted;
	t_tok	*insert;
	t_tok	*temp;
	int		i;

	i = 1;
	splitted = extract(lst->token);
	if (!splitted)
		return (ft_free_tok(head), clean_exit(data, 0), 0);
	free(lst->token);
	lst->token = ft_strdup(splitted[0]);
	while (splitted[i])
	{
		insert = lstnew_token2(ft_strdup(splitted[i]));
		temp = lst->next;
		lst->next = insert;
		insert->next = temp;
		lst = lst->next;
		i++;
	}
	ft_free_dble_array((void **)splitted);
	return (i);
}

void	clean_token(t_tok **lst, t_data *data)
{
	t_tok	*tmp;
	int		i;

	i = 0;
	tmp = *lst;
	while (tmp)
	{
		if (has_a_sep (tmp->token) && (int)ft_strlen(tmp->token) > 1)
		{
			i = split_sep(tmp, lst, data);
			while (i > 0)
			{
				tmp = tmp->next;
				i--;
			}
		}
		else
			tmp = (tmp)->next;
	}
}
