#include "exec.h"


int	count_nodes(t_tok **lst)
{
	t_tok	*temp;
	int		nb_nodes;

	*lst = temp;
	while (temp)
	{
		if(!ft_strcmp(temp->token, "|"))
			nb_nodes++;
		temp = temp->next;
	}	
}

void	fill_node_with_tok(t_tok **lst, t_data **data)
{
	int		nb_nodes;	

	nb_nodes= count_nodes(lst);
	
}