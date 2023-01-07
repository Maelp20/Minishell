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

void	at_heredoc(t_tok *lst, t_data *data)
{
		(void)lst;
		(void)data;
}

void	app_dir(t_tok *lst, t_data *data)
{
		(void)lst;
		(void)data;
}

void	in_redir(t_tok **lst, t_tok *lst_node, t_data ** data, t_data *data_node)
{
	t_tok *temp;
	(void)lst;
	(void)data;
	printf("test\n");
	if (!lst_node->next)
		printf("blahblah\n");
	data_node->infile = lst_node->next->token;
	temp = lst_node;
	lst_node->prev->next = lst_node->next;
	lst_node = lst_node->next;
	printf("free %s\n", lst_node->token);
	printf("free1 %s\n", temp->token);
	free(temp->token);
	free(temp);

	// temp = lst_node;
	// lst_node->prev->next = lst_node->next;
	// free(temp->token);
	// free(temp);
}

void	out_redir(t_tok *lst, t_data *data)
{
		(void)lst;
		(void)data;
}

int	check_redir(t_tok **lst, t_tok *lst_node, t_data **data, t_data *data_node)
{
	if (!ft_strcmp(lst_node->token, "<<"))
		return (at_heredoc(lst_node, data_node), 1);
	else if (!ft_strcmp(lst_node->token , ">>"))
		return (app_dir(lst_node, data_node), 1);
	else if (!ft_strcmp(lst_node->token, "<"))
		return (in_redir(lst, lst_node, data, data_node),  1);
	else if (!ft_strcmp(lst_node->token, ">"))
		return (out_redir(lst_node, data_node), 1);
	else
		return (0);
}

void process_redir(t_tok **lst, t_data **data)
{
	t_tok *temp_tok;
	t_data *temp_data;

	temp_tok = *lst;
	temp_data = *data;
	printf("try\n");
	while (temp_data)
	{
		printf("try2\n");
		while(temp_tok && ft_strcmp(temp_tok->token, "|") != 0)
		{
			printf("process_redir\n");
			check_redir(lst, temp_tok ,data , temp_data);
			temp_tok = temp_tok->next;
		}
		temp_data = temp_data->next;z
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