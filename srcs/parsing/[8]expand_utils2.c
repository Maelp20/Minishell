/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [8]expand_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:54:33 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/27 20:04:37 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	write_status(char *temp)
{
	char	*status;
	int		k;
	int		l;

	k = 0;
	l = 0;
	status = ft_itoa(g_var.g_status);
	while (status[k])
	{
		temp[l] = status[k];
		l++;
		k++;
	}
	free(status);
	return (len_status(g_var.g_status));
}

int	write_t_envp(int *len, t_envp *tmp, char *temp)
{
	int	k;
	int	l;

	k = 0;
	l = 0;
	(*len) += (int)ft_strlen(tmp->var[1]);
	while (tmp->var[1][k])
	{
		temp[l] = tmp->var[1][k];
		l++;
		k++;
	}
	return (*len);
}

void	process_token(char *tk, int *i, char **temp)
{
	**temp = tk[*i];
	(*temp)++;
	(*i)++;
}

void	expand_extension(t_tok *tmp, int *dbl, int *sq, t_data **data)
{
	int		i;
	char	*temp;

	i = -1;
	while (tmp->token && tmp->token[++i])
	{
		if (tmp->token[i] == '\"')
			(*dbl)++;
		if (tmp->token[i] == '\'' && !((*dbl) % 2))
			(*sq)++;
		if (tmp->token[i] == '$' && !((*sq) % 2) && tmp->token[i + 1] != '\"'
			&& (tmp->token[i + 1] != ' ' || tmp->token[i + 1] != 0))
		{
			temp = ft_strdup(tmp->token);
			free (tmp->token);
			tmp->token = expand_from(temp, *data);
			free(temp);
			break ;
		}
	}
}
