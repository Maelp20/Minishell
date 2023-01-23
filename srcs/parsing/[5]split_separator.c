/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [5]split_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:58:23 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/23 15:29:52 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_tok_list(t_tok *list)
{
	t_tok	*current;
	int		i;

	current = list;
	i = 0;
	printf("tok list : \n");
	while (current)
	{
		i++;
		printf("%d %s\n", i, current->token);
		current = current->next;
	}
}

char	*fill_word(char *token, int len)
{
	int		i;
	char	*split;

	i = 0;
	split = malloc(sizeof(char) * (len + 1));
	while (i < len)
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
	while (i < nb_word)
	{
		len = len_word(token);
		extracted[i] = fill_word(token, len);
		token += len;
		i++;
	}
	extracted[i] = NULL;
	return (extracted);
}

void	split_sep(t_tok *lst)
{
	char	**splitted;
	t_tok	*insert;
	t_tok	*temp;
	int i;
	
	i = 0;
	splitted = extract(lst->token);
	free(lst->token);
	lst->token = ft_strdup(splitted[i]);
	printf("splitted[i] = %s\n", splitted[i]);
	//i++;
	while (splitted[++i])
	{
		//i++;
		printf("splitted[i] = %s\n", splitted[i]);
		insert = lstnew_token(ft_strdup(splitted[i]));
		temp = lst->next;
		lst->next = insert;
		insert->next = temp;
		lst = lst->next;
	}
	ft_free_dble_array((void **)splitted);
}

void	clean_token(t_tok **lst)
{
	t_tok	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->token && !is_sep((tmp)->token[0]) && has_a_sep ((tmp)->token))
		{
			split_sep(tmp);
			tmp = tmp->next;
		}
		else
			tmp = (tmp)->next;
	}
}
