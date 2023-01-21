/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [13]fill_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:05:32 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/21 13:34:24 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	printf_data_args(t_data *data)
{
	int	i;

	i = 0;
	while (data->args[i])
	{
		printf("data->args[%d] %s\n", i, data->args[i]);
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
		if (ft_strcmp(temp->token, "|"))
			nb_nodes++;
		temp = temp->next;
	}
	return (nb_nodes);
}

void	create_data_nodes(int nb_nodes, t_data **data, t_envp *envir)
{
	int		i;
	t_data	*temp;

	i = 0;
	temp = *data;
	while (i < nb_nodes)
	{
		lstadd_back_args(&temp, lstnew_args(envir));
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

void	create_data_args(t_tok **lst, t_data **data)
{
	t_tok	*temp;
	t_data	*data_tmp;
	int		i;
	int		j;

	temp = *lst;
	data_tmp = (*data);
	i = 0;
	while (temp && !ft_strcmp(temp->token, "|"))
	{
		i++;
		temp = temp->next;
	}
	data_tmp->args = ft_calloc(i + 1, sizeof(char*));
	temp = *lst;
	j = 0;
	while (i > 0 && temp && !ft_strcmp(temp->token, "|"))
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

void	fill_node_with_tok(t_tok **lst, t_data **data, t_envp *envir)
{
	int		nb_nodes;
	t_data	*data_temp;

	data_temp = *data;
	nb_nodes = count_nodes(lst);
	create_data_nodes(nb_nodes, data, envir);
	while (data_temp)
	{
		process_redir(lst, &data_temp);
		create_data_args(lst, &data_temp);
		data_temp = data_temp->next;
	}
}
