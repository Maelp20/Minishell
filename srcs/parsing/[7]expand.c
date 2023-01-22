/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [7]expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 03:10:13 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/22 18:07:36 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	write_expanded(char *str, char *temp, int len_env, t_data *data)
{
	t_envp	*tmp;
	int		len;
	int		k;
	int		l;

	k = 0;
	l = 0;
	len = 0;
	tmp = data->envp;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->var[0], len_env))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
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
		if (str[i] == '$' && !(sq % 2) && str[i + 1] != '\"')
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
		if (token[i] == '$' && !(sq % 2) && token[i + 1] != '\"')
		{
			temp += write_expanded(token + i + 1, temp, len_env(token, i + 1), data);
			i += len_env(token, i + 1) + 1;
			printf("i %d\n", i);
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
	printf("%c\n", token[i]);
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
		while (tmp->token[++i])
		{
			if (tmp->token[i] == '\"')
				dbl++;
			if (tmp->token[i] == '\'' && !(dbl % 2))
				sq++;
			if (tmp->token[i] == '$' && !(sq % 2))
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
