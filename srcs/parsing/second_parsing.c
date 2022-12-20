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

void	ft_sa(t_tok *lst)
{
	t_tok	*tmp;

	if (!lst || !lst->next)
		return ;
	tmp = lst->next;
	lst->next = lst->next->next;
	tmp->next = lst;
	lst = tmp;
}

t_tok	*lstnew_token2(char *content, t_tok *tail)
{
	t_tok  *dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->token = ft_strdup(content);
	dest->next = tail;
	return (dest);
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

int	split_sep(char *token, int i, t_tok *lst)
{
	int		j;
	char	*tmp;
	t_tok	*tail;
	
	j = i;
	tail = lst->next;
	printf("split sep token = %s\n", token);
	printf("split sep j = %d\n", j);
	printf("split sep i = %d\n", i);
	printf("bool %d\n", is_separator(token[j], token[j + 1]));
	if (is_separator(token[j], token[j + 1]) == 2)
		j += 2;
	else if (is_separator(token[j], token[j + 1]) == 1)
		j += 1;
	else
	{
		while(token[j] && !is_separator(token[j], token[j + 1]))
			j++;
	}
	printf("split sep j - i + 1 = %d\n", j - i + 1);
	tmp = malloc(sizeof(char) * (j - i + 1));
	if (!tmp)
		return (-2);
	j = -1;
	printf("split sep before fill i = %d\n", i);
	if (is_separator(token[i], token[i + 1]) == 2)
	{
		while (j < 1)
		{	
			printf("token[i] = %c\n", token[i]);
			tmp[++j] = token[i];
			i++;
		}
	}
	else if (is_separator(token[i], token[i + 1]) == 1)
	{
		tmp[++j] = token[i];
	}
	else
	{
		while(token[i] && !is_separator(token[i], token[i + 1]))
		{
			tmp[++j] = token[i];
				i++;
		}

	}
	tmp[++j] = '\0';
	printf("split sep tmp = %s\n", tmp);
	printf("lst->next->token = %s\n", lst->next->token);
	printf("tail->token = %s\n", tail->token);
	lst->next = lstnew_token2(tmp, tail);
	printf("lst->next->token = %s\n", lst->next->token);
	printf("lst->next->next->token = %s\n", lst->next->next->token);
	ft_sa(lst);
	lst = lst->next;
	//printf("incr lst %s\n", lst->token);
	return (free(tmp), i);
}

void	clean_token(t_tok **lst)
{
	int i;
	int j;
	char *tmp;
	t_tok *del;
	t_tok *head;

	head = *lst;
	while (*lst)
	{
		del = *lst;
		if (has_a_sep ((*lst)->token))
		{
			tmp = ft_strdup((*lst)->token);
			printf("%s\n", tmp);
			free((*lst)->token);
			i = 0;
			j = 0;
			while(tmp[i])
			{
				i = split_sep(tmp, i, *lst);
				j++;
				printf("tmp[i] = %c\n", tmp[i]);
				printf("clean token i = %d\n", i);
			}
			if(!(*lst)->next)
				break;
			else
				*lst = (*lst)->next;
			free(del);
		}
		else
			*lst = (*lst)->next;
	}
	print_tok_list(*lst);
}