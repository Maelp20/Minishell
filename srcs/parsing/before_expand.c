#include "exec.h"


int	is_separator(char *str)
{
	int i;

	i = 0;
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
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

char **extract_args(t_tok **lst, int pos)
{
	int i; 
	char **dest;

	i = 0;
	dest = malloc(sizeof(char *) * pos);
	while ((*lst) && i < pos)
	{
		dest[i] = ft_strdup((*lst)->token);
		(*lst) = (*lst)->next;
		i++;
	}
	return (dest);
}

void	split_lst_operator(t_tok **lst, t_data **data)
{
	(void)data;
	int	pos;
	pos = 0;
	// while((*lst))
	// {
	//  	printf("%s\n", (*lst)->token);
	//  	(*lst) = (*lst)->next;
	// }
	pos = count_non_separators((*lst));

}
