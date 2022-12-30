/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:58:23 by yanthoma          #+#    #+#             */
/*   Updated: 2022/12/30 15:56:40 by yanthoma         ###   ########.fr       */
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
			while (token[i] && !is_separator(token[i]))
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


char *fill_word(char *token, int len)
{
	int	i;
	char *split;

	i = 0;
	// printf("token[i] = %s len = %d\n", token, len);
	// printf("token fill word[%c]\n",token[i]);
	split = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		split[i] =token[i]; 
		//printf("token[i] = %c split[i] = %c\n", token[i], split[i]);
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
	//printf("nb_word %d\n", nb_word);
	extracted = malloc(sizeof(char *) * (nb_word + 1));
	while (i < nb_word)
	{
		len = len_word(token);
		// printf("len %d\n", len);
		// printf("token %s\n", token);
		// printf("token[%c]\n",token[0]);
		// printf("i = %d\n", i);
		extracted[i] = fill_word(token, len);
		token += len;
		i++;
	}
	extracted[i] = '\0';
	return (extracted);
}

t_tok	*split_sep(t_tok *lst)
{
	int 	i;
	char 	**splitted;
	t_tok	*insert;
	t_tok	*temp;

	i = 0;
	splitted = extract(lst->token);
	free(lst->token);
	lst->token = ft_strdup(splitted[0]);
	while (splitted[++i])
	{
		insert = lstnew_token(ft_strdup(splitted[i]));
		temp = lst->next;
		lst->next = insert;
		insert->next = temp;
		lst = lst->next;
	}
	return (lst);
	// while (splitted[i])
	// {
	// 	printf("splitted[%d] %s\n", i, splitted[i]);
	// 	i++;
	// }
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
			tmp = split_sep(tmp);
			printf("tmp = %s\n", tmp->token);
			tmp = tmp->next;
		}
		else
			tmp = (tmp)->next;
	}
	print_tok_list(*lst);
}