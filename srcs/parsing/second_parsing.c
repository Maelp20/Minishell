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
	
	j = i;
	if (is_separator(token[j], token[j + 1]) == 2)
		j += 2;
	else if (is_separator(token[j], token[j + 1]) == 1)
		j += 1;
	else
	{
		while(token[j] && !is_separator(token[j], token[j + 1]))
			j++;
	}
	tmp = malloc(sizeof(char) * (j - i + 1));
	if (!tmp)
		return (-2);
	j = -1;
	i--;
	if (is_separator(token[++i], token[i + 1]) == 2)
	{
		tmp[++j] = token[i];
		tmp[++j] = token[++i];
	}
	else if (is_separator(token[i], token[i + 1]) == 1)
	{
		tmp[++j] = token[i];
	}
	else
	{
		while(token[i] && !is_separator(token[i], token[i + 1]))
			tmp[++j] = token[++i];
	}
	tmp[++j] = '\0';
	lst->next = lstnew_token(tmp);
	return (free(lst), free(tmp), ++i);
}

void	clean_token(t_tok **lst)
{
	int i; 
	char *tmp;

	while (*lst)
	{
		if (has_a_sep ((*lst)->token))
		{
			tmp = ft_strdup((*lst)->token);
			free((*lst)->token);
			i = 0;
			while(tmp[i])
				i = split_sep(tmp, i, *lst);
			free(tmp);
		}
		*lst = (*lst)->next;
	}
}