/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:58:23 by yanthoma          #+#    #+#             */
/*   Updated: 2022/12/28 19:03:35 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


void print_tok_list(t_tok *list)
{
    t_tok *current = list;
    while (current)
    {
        printf("%s\n", current->token);
        current = current->next;
    }
}

int	is_separator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int has_a_sep(char *token)
{
	int i;

	i = 0;
	while(token[i])
	{
		if (token[i] == '>' || token[i] == '<' || token [i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	countword(char *token)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	
	while (token[i])
	{
		if (!is_separator(token[i]))
		{
			j++;
			while (token[i])
				i++;
		}
		else
		{
			j++;
			while (token[i] && is_separator(token[i]))
				i++;
		}
	}
	return (j);
}


char *fill_word(char *token)
{
	int	i;
	char *split;

	i = 0;	
	while (token[i])
	{
		if (!is_separator(token[i]))
		{
			while (token[i])
			{
				token[i] = split[i];
				i++;
			}
		}
		else
		{
			while (token[i] && is_separator(token[i]))
			{
				token[i] = split[i];
				i++;
			}
		}
	}
	split[i] = '\0';
	return (split);
}

int	len_word(char *token)
{
	int	i;

	while (token[i])
	{
		if (!is_separator(token[i]))
		{
			while (token[i] && !is_separator(token[i]))
				i++;
			return (i);
		}
		else
		{
			while (token[i] && is_separator(token[i]))
				i++;
			return (i);
		}
	}
	return (i);
}

char **extract(char *token)
{
	int		nb_word;
	char	**extracted;
	int 	i;
	int		len;

	i = 0;
	nb_word = countword(token);
	extracted = malloc(sizeof(char *) * (nb_word + 1));
	while (i < nb_word)
	{
		len = len_word(token);
		extracted[i] = malloc(sizeof(char) * (len + 1));
		fill_word(extracted[i]);
		token += len;
	}
	extracted[i] = '\0';
	
}

void	split_sep(t_tok *lst)
{
	 int i;
	 char **splitted;

	i = 0;
	splitted = extract(lst->token);

}

void	clean_token(t_tok **lst)
{
	int i;
	int j;
	t_tok *tmp;
	
	tmp = *lst;
	while (tmp)
	{
		if (has_a_sep ((tmp)->token))
		{
			split_sep(tmp);
		}
		else
			tmp = (tmp)->next;
	}
	print_tok_list(*lst);
}