#include "exec.h"

void	printf_data_args(t_data *data)
{
	int i = 0;

	while (data->args[i])
	{
		printf("data->args[%d] %s\n",i, data->args[i]);
		i++;
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
		if(ft_strcmp(temp->token, "|"))
			nb_nodes++;
		temp = temp->next;
	}
	return (nb_nodes);
}

void	create_data_nodes(int nb_nodes,t_data **data, t_envp *envir)
{
	int i;
	t_data *temp;
	i = 0;
	temp = *data;
	while (i < nb_nodes)
	{
		lstadd_back_args(&temp,lstnew_args(envir));
		i++;
	}
}

void process_node(t_tok **node, t_tok **lst)
{
	t_tok *temp;

	temp = (*node)->next;
	tok_del_one(*node);
	*node = temp;
	*lst = temp;
}

int	is_builtin(char *token)
{

	if (ft_strcmp(token, "cd"))
		return(1);
	else if (ft_strcmp(token, "echo"))
		return(1);
	else if (ft_strcmp(token, "env"))
		return(1);
	else if (ft_strcmp(token, "exit"))
		return(1);
	else if (ft_strcmp(token, "export"))
		return(1);
	else if (ft_strcmp(token, "pwd"))
		return(1);
	else if (ft_strcmp(token, "unset"))
		return(1);
	return (0);
}


void	create_data_args(t_tok **lst, t_data **data)
{
	t_tok *temp;
	t_data	*data_tmp;
	int	i;
	int j;

	temp = *lst;
	data_tmp = (*data);
		i = 0;
		while(temp && !ft_strcmp(temp->token, "|"))
		{
			i++;
			temp = temp->next;
		}
		data_tmp->args = ft_calloc(sizeof(char*), i + 1);
		temp = *lst;
		j = 0;
		while(i > 0  && temp && !ft_strcmp(temp->token, "|"))
		{
			if (j == 0 && is_builtin(temp->token))
			 	data_tmp->is_builtin = 1;
			data_tmp->args[j] = ft_strdup(temp->token);
			process_node(&temp, &(*lst));
			j++;
			i--;
		}
		if (temp && ft_strcmp(temp->token, "|"))
		{
			process_node(&temp, &(*lst));
			data_tmp->out_pipe = 1;
			data_tmp->next->in_pipe = 1;
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
		//(*lst_node) = (*lst_node)->next;
		if (temp->prev->next)
		{	
			temp->prev->next->prev = temp->prev;
			//temp->next = temp->next;
		}
	}
	tok_del_one(temp);
	tok_del_one(temp2);
}

void	at_heredoc(t_tok **lst, t_tok **lst_node, t_data ** data, t_data *data_node)
{
    (void)data;
	if (data_node->is_heredoc)
		free(data_node->is_heredoc);
	if (ft_strcmp((*lst_node)->token, (*lst)->token))
	{
		data_node->is_heredoc = ft_strdup((*lst_node)->next->token);
		data_node->is_append = 1;
		one_node(lst);
		return;
	}	
    if (!(*lst_node)->next)
        clean_parsing(lst, data);
    data_node->outfile = ft_strdup((*lst_node)->next->token);
	if (!data_node->outfile)
			clean_parsing(lst, data);
	data_node->is_append = 1;
	multi_node(lst_node, lst);
}

void	app_dir(t_tok **lst, t_tok **lst_node, t_data ** data, t_data *data_node)
{
    (void)data;
	if (data_node->outfile)
		free(data_node->outfile);
	if (ft_strcmp((*lst_node)->token, (*lst)->token))
	{
		data_node->outfile = ft_strdup((*lst_node)->next->token);
		data_node->is_append = 1;
		one_node(lst);
		return;
	}	
    if (!(*lst_node)->next)
        clean_parsing(lst, data);
    data_node->outfile = ft_strdup((*lst_node)->next->token);
	if (!data_node->outfile)
			clean_parsing(lst, data);
	data_node->is_append = 1;
	multi_node(lst_node, lst);
}

void    out_redir(t_tok **lst, t_tok **lst_node, t_data ** data, t_data *data_node)
{
    (void)data;
	if (data_node->outfile)
		free(data_node->outfile);
	if (ft_strcmp((*lst_node)->token, (*lst)->token))
	{
		data_node->outfile = ft_strdup((*lst_node)->next->token);
		one_node(lst);
		return;
	}	
    if (!(*lst_node)->next)
        clean_parsing(lst, data);
    data_node->outfile = ft_strdup((*lst_node)->next->token);
	if (!data_node->outfile)
			clean_parsing(lst, data);
	multi_node(lst_node, lst);
}

void    in_redir(t_tok **lst, t_tok **lst_node, t_data ** data, t_data *data_node)
{
	if (data_node->infile)
		free(data_node->infile);
	if (ft_strcmp((*lst_node)->token, (*lst)->token))
	{
		data_node->infile = ft_strdup((*lst_node)->next->token);
		if (!data_node->infile)
			clean_parsing(lst, data);
		one_node(lst);
		return;
	}	
    if (!(*lst_node)->next)
        clean_parsing(lst, data);
    data_node->infile = ft_strdup((*lst_node)->next->token);
	if (!data_node->infile)
			clean_parsing(lst, data);
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
        while(lst && temp_tok && !ft_strcmp(temp_tok->token, "|"))
        {
            if(lst && !check_redir(lst, &temp_tok ,data , temp_data))
            	temp_tok = temp_tok->next;
			else
				temp_tok = *lst;
        }
}

void	fill_node_with_tok(t_tok **lst, t_data **data, t_envp *envir)
{
	int		nb_nodes;
	t_data *data_temp;
	
	data_temp = *data;
	nb_nodes = count_nodes(lst);
	create_data_nodes(nb_nodes, data, envir);
	while(data_temp)
	{
		process_redir(lst, &data_temp);
		create_data_args(lst, &data_temp);
		data_temp = data_temp->next;
	}
		
}