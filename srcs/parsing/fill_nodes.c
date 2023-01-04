#include "exec.h"


void	count_nodes(t_tok *lst, t_data **data)
{
	t_tok	*temp;
	t_data	*head;
	t_data	*node;
	int		nb_nodes;	

	nb_nodes =0;
	temp = lst;
	head = NULL;
	*data = &head;
	while (temp)
	{
		if(!ft_strcmp(temp->token, "|"))
			nb_nodes++;
		temp = temp->next;
	}
	if (nb_nodes > 1)
		(*data)->outpipe = 1;
	while (nb_nodes > 0)
	{
		node = ft_calloc(1, sizeof(t_data));
		ft_bzero(node, sizeof(t_data));

	}
	
}

void	fill_node_with_tok(t_tok **lst, t_data **data)
{
	int		nb_nodes;	

	
	
}