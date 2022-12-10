#include "exec.h"


int	is_separator(char *str)
{
	int i;

	i = 0;
	if (str[i] == '|')
		return (1);
	else 
		return (0);
}
int count_non_separators(t_tok *lst)
{
	int count;

	count = 0;
	while (lst && !(is_separator(lst->token)))
	{
    	count++;
    	lst = lst->next;
	}
	return count;
}

char **extract_args(t_tok *lst, int pos)
{
	int i; 
	char **dest;

	i = 0;
	dest = malloc(sizeof(char *) * pos);
	while (lst && i < pos)
	{
		printf("extract token %s\n", lst->token);
		dest[i] = ft_strdup(lst->token);
		lst = lst->next;
		i++;
	}
	dest[pos]= '\0';
	return (dest);
}

void	split_lst_operator(t_tok **lst, t_data **data)
{
	int	pos;
	pos = 0;
	// while((*lst))
	// {
	//  	printf("%s\n", (*lst)->token);
	//  	(*lst) = (*lst)->next;
	// }
	while((*lst))
	{
		pos = count_non_separators((*lst));
		printf("%d\n", pos);
	 	if (pos)
		{
			(*data)->args = extract_args((*lst), pos);
			while (--pos)
				(*lst) = (*lst)->next;
		}
		pos = 0;
	 	(*lst) = (*lst)->next;
	}
	int i;
	while((*data))
	{
	 	i = 0;
		while ((*data)->args[i])
		{
			printf("%s\n", (*data)->args[i]);
			i++;
		}
	 	(*data) = (*data)->next;
	}
}
