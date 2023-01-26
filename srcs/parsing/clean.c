/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:47:57 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/26 17:40:53 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	disp_error(t_tok **tok_lst, t_data **data, char *token)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	ft_free_data_pars(*data);
	ft_free_tok(tok_lst);
	g_var.g_status = 2;
}

void	clean_parsing(t_tok **lst, t_data **data)
{
	perror("malloc :");
	ft_free_tok(lst);
	ft_free_data(*data);
}

void	ft_free_data_pars(t_data *data)
{
	//print_tout_huehue(&data);
	t_data	*tmp;

    while (data)
    {
		tmp = data;
		data = data->next;
		if (tmp->args)
		{
			ft_free_dble_array((void **)tmp->args);
			tmp->args = NULL;
		}
		if (tmp->env)
		{
			ft_free_dble_array((void **)tmp->env);
			tmp->env = NULL;
		}
		if (tmp->fds)
			free(tmp->fds);
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		if (tmp->is_heredoc)
			free(tmp->is_heredoc);
		if (tmp->infile)
			free(tmp->infile);
		if (tmp->outfile)
			free(tmp->outfile);
		if(tmp)
			free(tmp);
	}
}

void	ft_free_tok(t_tok **lst_tok)
{
	t_tok	*tmp;

	while (*lst_tok)
	{
		tmp = *lst_tok;
		*lst_tok = (*lst_tok)->next;
		if (tmp->token)
			free(tmp->token);
		free (tmp);
	}
}
