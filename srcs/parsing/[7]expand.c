/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [7]expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 03:10:13 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/27 20:05:22 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	write_expanded(char *str, char *temp, int len_env, t_data *data)
{
	t_envp	*tmp;
	int		len;

	len = 0;
	tmp = data->envp;
	if (*str == '?')
	{
		return (write_status(temp));
	}
	while (tmp && len_env > 0)
	{
		if (len_env == ((int)ft_strlen(tmp->var[0]) - 1)
			&& ft_strncmp(str, tmp->var[0], len_env) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp && len_env > 0)
		write_t_envp(&len, tmp, temp);
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

void	fill_expand(char *temp, char *tk, t_data *data)
{
	int		dbl;
	int		sq;
	int		i;

	i = 0;
	sq = 2;
	dbl = 2;
	while (tk[i])
	{
		if (tk[i] == '\"')
			dbl++;
		if (tk[i] == '\'' && !(dbl % 2))
			sq++;
		if (tk[i] == '$' && !(sq % 2) && tk[i + 1] != '\"'
			&& tk[i + 1] != 0)
		{
			temp += write_expanded(tk + i + 1, temp, len_env(tk, i + 1), data);
			i += len_env(tk, i + 1) + 1;
		}
		else
			process_token(tk, &i, &temp);
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
	t_tok	*tmp;

	sq = 2;
	dbl = 2;
	tmp = *lst;
	while (tmp)
	{
		expand_extension(tmp, &dbl, &sq, data);
		tmp = tmp->next;
	}
}
