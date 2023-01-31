/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:17:27 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/31 13:03:20 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	update_shlvl(t_envp *dest, char *temp)
{
	temp = ft_strdup(dest->var[1]);
	if (!temp)
		ft_free_dble_array((void **)dest->var);
	free(dest->var[1]);
	dest->var[1] = ft_itoa(ft_atoi(temp) + 1);
	if (!dest->var[1])
		ft_free_dble_array((void **)dest->var);
	free(temp);
}

t_envp	*lstnew_env(char **content)
{
	t_envp	*dest;
	char	*temp;

	if (content)
	{
		dest = ft_calloc(1, sizeof(t_envp));
		if (!dest)
			return (NULL);
		dest->var = content;
		temp = dest->var[0];
		dest->var[0] = ft_strjoin(dest->var[0], "=");
		if (!dest->var[0])
			return (ft_free_dble_array((void **)dest->var), NULL);
		free(temp);
		if (ft_strcmp(dest->var[0], "SHLVL="))
			update_shlvl(dest, temp);
		dest->next = NULL;
		return (dest);
	}
	return (NULL);
}

//protect the malloc otherwise it's a fail
char	**split_at_first_equal(char *input)
{
	char		**output;
	char		*equal_pos;
	size_t		first_len;
	size_t		second_len;

	output = ft_calloc(3, sizeof(char *));
	equal_pos = ft_strchr(input, '=');
	if (equal_pos)
	{
		first_len = equal_pos - input + 1;
		output[0] = ft_substr(input, 0, first_len - 1);
		if (!output[0])
			return (ft_free_dble_array((void **)output), NULL);
		second_len = ft_strlen(input) - first_len + 1;
		output[1] = ft_substr(input, first_len, second_len);
		if (!output[1])
			return (ft_free_dble_array((void **)output), NULL);
		output[2] = NULL;
		return (output);
	}
	else
		return (NULL);
}

t_envp	*get_env(char **envi)
{
	int		i;
	t_envp	*head;
	t_envp	*node;
	t_envp	**tail;

	i = 0;
	head = NULL;
	tail = &head;
	while (envi[i])
	{
		node = lstnew_env(split_at_first_equal(envi[i]));
		if (!node)
			return (NULL);
		*tail = node;
		tail = &node->next;
		i++;
	}
	return (head);
}
