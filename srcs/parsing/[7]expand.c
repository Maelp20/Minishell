/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [7]expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 03:10:13 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/26 17:40:42 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	write_expanded(char *str, char *temp, int len_env, t_data *data)
{
	t_envp	*tmp;
	int		len;
	int		k;
	int		l;
	int		comp_len;

	k = 0;
	l = 0;
	len = 0;
	tmp = data->envp;
	if (*str == '?')
	{
		char *status = ft_itoa(g_var.g_status);
		while (status[k])
		{
			temp[l] = status[k];
			l++;
			k++;
		}
		free(status);
		return (len_status(g_var.g_status));
	}
	while (tmp && len_env > 0)
	{
		comp_len = (int)ft_strlen(tmp->var[0]) - 1;
		if (len_env == comp_len && ft_strncmp(str, tmp->var[0], len_env) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp && len_env > 0)
	{
		len += (int)ft_strlen(tmp->var[1]);
		while (tmp->var[1][k])
		{
			temp[l] = tmp->var[1][k];
			l++;
			k++;
		}
	}
	return (len);
}

int	trigger_expand(char *str, int i, t_data *data)
{
	int		dbl;
	int		sq;
	int		len;

	len = 0;
	sq = 2;
	dbl = 2;
	while (str[i])
	{
		if (str[i] == '\"')
			dbl++;
		if (str[i] == '\'' && !(dbl % 2))
			sq++;
		if (str[i] == '$' && !(sq % 2) && str[i + 1] != '\"' && str[i + 1] != 0)
		{
			len += len_expanded(str + i + 1, len_env(str, i + 1), data);
			i += len_env(str, i + 1) + 1;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	fill_expand(char *temp, char *token, t_data *data)
{
	int		dbl;
	int		sq;
	int		i;

	i = 0;
	sq = 2;
	dbl = 2;
	while (token[i])
	{
		if (token[i] == '\"')
			dbl++;
		if (token[i] == '\'' && !(dbl % 2))
			sq++;
		if (token[i] == '$' && !(sq % 2) && token[i + 1] != '\"' && token[i + 1] != 0)
		{
			temp += write_expanded(token + i + 1, temp, len_env(token, i + 1), data);
			i += len_env(token, i + 1) + 1;
		}
		else
		{
			*temp = token[i];
			temp++;
			i++;
		}
	}
	*temp = 0;
}

char	*expand_from(char *token, t_data *data)
{
	char	*temp;
	int		i;

	i = 0;
	i = trigger_expand(token, i, data);
	temp = ft_calloc(i + 1, sizeof(char));
	fill_expand(temp, token, data);
	return (temp);
}

void	expand(t_tok **lst, t_data **data)
{
	int		dbl;
	int		sq;
	int		i;
	char	*temp;
	t_tok	*tmp;

	sq = 2;
	dbl = 2;
	tmp = *lst;
	while (tmp)
	{
		i = -1;
		while (tmp->token && tmp->token[++i])
		{
			if (tmp->token[i] == '\"')
				dbl++;
			if (tmp->token[i] == '\'' && !(dbl % 2))
				sq++;
			if (tmp->token[i] == '$' && !(sq % 2) && tmp->token[i + 1] != '\"' && (tmp->token[i + 1] != ' ' || tmp->token[i + 1] != 0))
			{
				temp = ft_strdup(tmp->token);
				free (tmp->token);
				tmp->token = expand_from(temp, *data);
				free(temp);
				break ;
			}
		}
		tmp = tmp->next;
	}
}
