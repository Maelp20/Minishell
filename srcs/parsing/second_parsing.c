/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:58:23 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/07 17:25:16 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


void print_tok_list(t_tok *list)
{
    t_tok *current = list;
	int i;
	i = 0;
	printf("tok list : \n");
    while (current)
    {
		i++;
        printf("%d %s\n",i, current->token);
		if (current->prev)
			printf("previous %s\n", current->prev->token);
        current = current->next;
    }
}

int	check_separator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}


int	is_separator(char c1, char c2)
{
    if(c2 && ((c1 == '>'  && c2 == '>') || (c1 == '<' && c2 == '<')))
        return (2);
    else if (c1 == '>' || c1 == '<' || c1 == '|')
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
		if (!check_separator(token[i]))
		{
			j++;
			while (token[i] && !check_separator(token[i]))
				i++;
		}
		else
		{
			j++;
    		if (is_separator(token[i], token[i + 1]) == 2)
				i += 2;
   			else if (is_separator(token[i], token[i + 1]) == 1)
				i += 1;
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
	extracted[i] = NULL;
	return (extracted);
}

t_tok	*split_sep(t_tok *lst)
{
	char 	**splitted;
	t_tok	*insert;
	t_tok	*temp;

	splitted = extract(lst->token);
	free(lst->token);
	lst->token = ft_strdup(splitted[0]);
	while (*(++splitted))
	{
		insert = lstnew_token(ft_strdup(*splitted));
		temp = lst->next;
		lst->next = insert;
		insert->next = temp;
		lst = lst->next;
	}
	return (lst);
}

void	clean_token(t_tok **lst)
{
	// int i;
	// int j;
	t_tok *tmp;
	
	tmp = *lst;
	while (tmp)
	{
		if (!is_sep((tmp)->token[0]) && has_a_sep ((tmp)->token))
		{
			tmp = split_sep(tmp);
			tmp = tmp->next;
		}
		else
			tmp = (tmp)->next;
	}
}