/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [13]fill_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:05:32 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/31 01:01:09 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	count_nodes(t_tok **lst)
{
	t_tok	*temp;
	int		nb_nodes;

	nb_nodes = 0;
	temp = *lst;
	while (temp)
	{
		if (ft_strcmp(temp->token, "|"))
			nb_nodes++;
		temp = temp->next;
	}
	return (nb_nodes);
}

void	create_data_nodes(int nb_nodes, t_data **data, t_envp *envir)
{
	int		i;

	i = 0;
	while (i < nb_nodes)
	{
		lstadd_back_args(data, lstnew_args(envir));
		i++;
	}
}

int	is_builtin(char *token)
{
	if (ft_strcmp(token, "cd"))
		return (1);
	else if (ft_strcmp(token, "echo"))
		return (1);
	else if (ft_strcmp(token, "env"))
		return (1);
	else if (ft_strcmp(token, "exit"))
		return (1);
	else if (ft_strcmp(token, "export"))
		return (1);
	else if (ft_strcmp(token, "pwd"))
		return (1);
	else if (ft_strcmp(token, "unset"))
		return (1);
	return (0);
}

int	create_data_args(t_tok **lst, t_data **data)
{
	t_tok	*temp;
	t_data	*data_tmp;
	int		i[2];

	temp = *lst;
	data_tmp = (*data);
	ft_bzero(i, sizeof(int) * 2);
	trigger_creation(&i[0], temp, data_tmp);
	if (i[0] == 0 && temp && !ft_strcmp(temp->token, "|"))
		return (0);
	// if (temp && ft_strcmp(temp->token, "|"))
	// {
	// 	process_node(&temp, &(*lst));
	// 	data_tmp->out_pipe = 1;
	// 	if (data_tmp->next)
	// 		data_tmp->next->in_pipe = 1;
	// }
	temp = *lst;
	while (i[0]-- > 0 && temp && !ft_strcmp(temp->token, "|"))
	{
		if (i[1] == 0 && is_builtin(temp->token))
			data_tmp->is_builtin = 1;
		data_tmp->args[i[1]++] = ft_strdup(temp->token);
		process_node(&temp, &(*lst));
	}
	if (temp && ft_strcmp(temp->token, "|"))
	{
		process_node(&temp, &(*lst));
		data_tmp->out_pipe = 1;
		if (data_tmp->next)
			data_tmp->next->in_pipe = 1;
	}
	return (1);
}

void	fill_node_with_tok(t_tok **lst, t_data **data, t_envp *envir)
{
	int		nb_nodes;
	t_data	*data_temp;

	if (!lst)
		return ;
	nb_nodes = count_nodes(lst);
	create_data_nodes(nb_nodes, data, envir);
	data_temp = *data;
	while (data_temp)
	{
		process_redir(lst, &data_temp);
		if (create_data_args(lst, &data_temp) == 0 && !*lst)
			return ;
		data_temp = data_temp->next;
	}
}
