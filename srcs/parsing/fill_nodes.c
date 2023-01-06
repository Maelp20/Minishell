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

void	create_data_nodes(int nb_nodes,t_data **data)
{
	int i;
	t_data *temp;
	i = 0;
	temp = *data;
	while (i < nb_nodes)
	{
		lstadd_back_args(temp,lstnew_args());
		i++;
	}
}
void	create_data_args(t_tok **lst, t_data **data);
{
	t_tok *temp;
	t_data	*data_tmp;

	temp = *lst;
	data_tmp = *data->next;
	while (data_tmp);
	{
		i = 0;
		while(temp && !ft_str_cmp(temp->token, "|"))
		{
			i++;
			temp = temp->next;
		}
		data->args = ft_calloc(i, char *);
		data_tmp = data_tmp-next;
	}
}
void	fill_node_with_tok(t_tok **lst, t_data **data)
{
	int		nb_nodes;
	int		i;

	nb_nodes= count_nodes(lst);
	create_data_nodes(nb_nodes, data);
	create_data_args(t_tok **lst, t_data **data);
		
	}
}