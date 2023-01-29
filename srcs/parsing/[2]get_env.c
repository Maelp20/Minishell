/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:17:27 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/29 00:50:04 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_env(t_envp *list)
{
	t_envp	*current;

	current = list;
	while (current)
	{
		printf("%s%s\n", current->var[0], current->var[1]);
		current = current->next;
	}
}

t_envp	*lstnew_env(char **content)
{
	t_envp	*dest;
	char	*temp;


	dest = ft_calloc(1, sizeof(t_envp));
	dest->var = ft_calloc(3, sizeof(char *));
	if (!dest)
		return (free(dest->var), free(dest), NULL);
	dest->var[0] = ft_strdup(content[0]);
	dest->var[1] = ft_strdup(content[1]);
	dest->var[2] = NULL;
	temp = dest->var[0];
	dest->var[0] = ft_strjoin(dest->var[0], "=");
	free(temp);
	if (ft_strcmp(dest->var[0], "SHLVL="))
	{
		temp = ft_strdup(dest->var[1]);
		free (dest->var[1]);
		dest->var[1] = ft_itoa(ft_atoi(temp) + 1);
		free (temp);
		temp = NULL;
	}
	dest->next = NULL;
	return (ft_free_dble_array((void **)content), dest);
}

//protect the malloc otherwise it's a fail
char	**split_at_first_equal(char *input)
{
	char		**output;
	char		*equal_pos;
	size_t		first_len;
	size_t		second_len;

	output = ft_calloc(3, sizeof(char *));
	if (!output)
		return (NULL);
	equal_pos = ft_strchr(input, '=');
	if (equal_pos)
	{
		first_len = equal_pos - input + 1;
		output[0] = ft_substr(input, 0, first_len - 1);
		second_len = ft_strlen(input) - first_len + 1;
		output[1] = ft_substr(input, first_len, second_len);
		output[2] = NULL;
		return (output);
	}
	else
		return (free(output), NULL);
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
			return (ft_envpclear(&head), NULL);
		*tail = node;
		tail = &node->next;
		i++;
	}
	return (head);
}
