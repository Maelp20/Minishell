#include "exec.h"

void	printf_data_args(t_data *data)
{
	t_data *temp;

	temp = data;
	while (temp)
	{
		printf("%s\n", temp->args[0]);
		temp = temp->next;
	}
}

int	count_nodes(t_tok **lst)
{
	t_tok	*temp;
	int		nb_nodes;

	nb_nodes = 0;
	temp = *lst;
	while (temp)
	{
		if(!ft_strcmp(temp->token, "|"))
			nb_nodes++;
		temp = temp->next;
	}
	return (nb_nodes);
}

void	create_data_nodes(int nb_nodes,t_data **data)
{
	int i;
	t_data *temp;
	i = 0;
	temp = *data;
	while (i < nb_nodes)
	{
		lstadd_back_args(&temp,lstnew_args());
		i++;
	}
}
void	create_data_args(t_tok **lst, t_data **data)
{
	t_tok *temp;
	t_data	*data_tmp;
	int	i;

	temp = *lst;
	data_tmp = (*data)->next;
	while (data_tmp)
	{
		i = 0;
		while(temp && !ft_strcmp(temp->token, "|"))
		{
			i++;
			temp = temp->next;
		}
		data_tmp->args = ft_calloc(sizeof(char*), i);
		data_tmp->args[0][0] = i + '0';
		data_tmp = data_tmp->next;
	}
}

void	one_node(t_tok **lst)
{
	t_tok *temp;

	temp = (*lst)->next;
	tok_del_one(*lst);
	*lst = temp;
	temp = (*lst)->next;
	tok_del_one(*lst);
	*lst = temp;
}

void	multi_node(t_tok **lst_node, t_tok **lst)
{
	t_tok *temp;
	t_tok *temp2;

    temp = (*lst_node);
	temp2 = (*lst_node)->next;
	if ((*lst_node)->prev == NULL)
	{
		(*lst_node)->next->next->prev = NULL;
		*lst = (*lst_node)->next->next;
	}
	else
	{
    	(*lst_node)->prev->next = (*lst_node)->next->next;
		if (temp->prev->next)
			temp->prev->next->prev = temp->prev;
	}
	tok_del_one(temp);
	tok_del_one(temp2);
}

void	at_heredoc(t_tok **lst, t_tok **lst_node, t_data ** data, t_data *data_node)
{
    (void)data;
	if (ft_strcmp((*lst_node)->token, (*lst)->token))
	{
		data_node->is_heredoc = ft_strdup((*lst_node)->next->token);
		data_node->is_append = 1;
		one_node(lst);
		return;
	}	
    if (!(*lst_node)->next)
        printf("blahblah\n");
    data_node->outfile = ft_strdup((*lst_node)->next->token);
	data_node->is_append = 1;
	multi_node(lst_node, lst);
}

void	app_dir(t_tok **lst, t_tok **lst_node, t_data ** data, t_data *data_node)
{
    (void)data;
	if (ft_strcmp((*lst_node)->token, (*lst)->token))
	{
		data_node->outfile = ft_strdup((*lst_node)->next->token);
		data_node->is_append = 1;
		one_node(lst);
		return;
	}	
    if (!(*lst_node)->next)
        printf("blahblah\n");
    data_node->outfile = ft_strdup((*lst_node)->next->token);
	data_node->is_append = 1;
	multi_node(lst_node, lst);
}

void    out_redir(t_tok **lst, t_tok **lst_node, t_data ** data, t_data *data_node)
{
    (void)data;
	if (ft_strcmp((*lst_node)->token, (*lst)->token))
	{
		data_node->infile = ft_strdup((*lst_node)->next->token);
		one_node(lst);
		return;
	}	
    if (!(*lst_node)->next)
        printf("blahblah\n");
    data_node->infile = ft_strdup((*lst_node)->next->token);
	multi_node(lst_node, lst);
}

void    in_redir(t_tok **lst, t_tok **lst_node, t_data ** data, t_data *data_node)
{
    (void)data;
	if (ft_strcmp((*lst_node)->token, (*lst)->token))
	{
		data_node->outfile = ft_strdup((*lst_node)->next->token);
		one_node(lst);
		return;
	}	
    if (!(*lst_node)->next)
        printf("blahblah\n");
    data_node->outfile = ft_strdup((*lst_node)->next->token);
	multi_node(lst_node, lst);
}

int	check_redir(t_tok **lst, t_tok **lst_node, t_data **data, t_data *data_node)
{
	if (ft_strcmp((*lst_node)->token, "<<"))
		return (at_heredoc(lst, lst_node, data, data_node), 1);
	else if (ft_strcmp((*lst_node)->token , ">>"))
		return (app_dir(lst, lst_node, data, data_node), 1);
	else if (ft_strcmp((*lst_node)->token, "<"))
		return (in_redir(lst, lst_node, data, data_node),  1);
	else if (ft_strcmp((*lst_node)->token, ">"))
		return (out_redir(lst, lst_node, data, data_node), 1);
	else
		return (0);
}

void process_redir(t_tok **lst, t_data **data)
{
    t_tok *temp_tok;
    t_data *temp_data;

    temp_tok = *lst;
    temp_data = *data;
    while (temp_data)
    {
        while(lst && temp_tok && !ft_strcmp(temp_tok->token, "|"))
        {
            if(lst && !check_redir(lst, &temp_tok ,data , temp_data))
            	temp_tok = temp_tok->next;
			else
				temp_tok = *lst;
        }
        temp_data = temp_data->next;
    }
}

void	fill_node_with_tok(t_tok **lst, t_data **data)
{
	int		nb_nodes;

	nb_nodes = count_nodes(lst);
	create_data_nodes(nb_nodes, data);
	process_redir(lst, data);
	//create_data_args(lst, data);
	//printf_data_args(*data);
		
}