#include "exec.h"

int	is_to_split(char c)
{
	if ( c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void	replace_node(t_tok **lst, t_tok **tmp)
{
	//find the node to replace
	while (ft_strcmp((*lst)->token, (*lst)->token))
		(*lst) = (*lst)->next;
	//set the node to the first of tmp
	(*lst) = (*tmp);
	//go to the last node of tmp
	while ((*tmp) && (*tmp)->next)
		(*tmp) = (*tmp)->next;
	//set the end of tmp to the next
	if (*tmp)
		*tmp = (*lst)->next;
	//free the node to replace
	free(*lst);
}

int	split_pipe_and_chev(char *token, int i, t_tok **lst)
{
	int	j;
	char *tmp;
	
	j = i;
	while(token[j] && !is_to_split(token[j]))
		j++;
	tmp = malloc(sizeof(char) * (j - i + 1));
	if (!tmp)
		return (-2);
	j = -1;
	i--;
	while(!is_to_split(token[++i]))
		tmp[++j] = token[++i];
	return(i);
}

void	clean_token_lst(t_tok **lst)
{
	int			i;
	t_tok	**tmp;

	while ((*lst))
	{
		i = 0;
		while((*lst)->token[i])
		{
			if (is_to_split((*lst)->token[i]))
			{
				i = split_pipe_and_chev((*lst)->token, i, tmp);
				replace_node(lst, tmp);
			}
			i++;
		}
		(*lst) = (*lst)->next;
	}
}